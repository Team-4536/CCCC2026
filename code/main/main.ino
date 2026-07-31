//#define _USE_MATH_DEFINES
//#include <cmath>

const int right_enable_pin = 7;
const int right_dir_pin = 6;
const int left_enable_pin = 9;
const int left_dir_pin = 8;
const int LED_PIN = 13;
const int ECHO_PIN = 27;
const int TRIGGER_PIN = 26;

const double FULL_ROT_TIME = 1;

double getSonicDist();
bool obstacleAhead();
void forward(int speed);
void right(double degrees);
void left(double degrees);
double getDurFromDeg(double deg);
double getAngle(double d1, double d2, double angle);
double getWallLen(double d1, double d2, double angle);

double dist1;
double dist2;
double wallLen;
double errorAngle;

const double AVOID_DIST = 5; // in cm
const double TURN_ANGLE = 15; // in degrees

void setup()
{
  // put your setup code here, to run once:
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  dist1 = getSonicDist();

  Serial.begin(9600);
}

void loop()
{
  dist1 = getSonicDist();
  
  if (obstacleAhead())
  {
    right(TURN_ANGLE);
    dist2 = getSonicDist();
    wallLen = getWallLen(dist1, dist2, TURN_ANGLE);
    errorAngle = getAngle(dist1, dist1, TURN_ANGLE);

    if(errorAngle > 90){
      left(180-errorAngle);
    } else {
      right(errorAngle);
    }
  }
  else
  {
    forward(255);
  }


}

double getSonicDist()
{ // Contains code from the big DJ Orser

  // Send a HIGH Pulse to triggerPin that is 10us Long
  digitalWrite(TRIGGER_PIN, LOW);  // Trigger should already be low, just in case
  delayMicroseconds(2);            // This is just like delay() but in microseconds
  digitalWrite(TRIGGER_PIN, HIGH); // set HIGH
  delayMicroseconds(10);           // wait 10us
  digitalWrite(TRIGGER_PIN, LOW);  // set LOW

  double duration = pulseIn(ECHO_PIN, HIGH); // Measure pulse width on echoPin

  double distance = duration / 58.0; // Calc distance duration / speed_of_sound (cm/us)

  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

bool obstacleAhead()
{
  return dist1 < AVOID_DIST;
}

void forward(int speed)
{
  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, speed);
  analogWrite(left_enable_pin, speed);
}

void right(double degrees)
{
  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, LOW);
  analogWrite(right_enable_pin, 255);
  analogWrite(left_enable_pin, 255);
  delay(getDurFromDeg(degrees));
}

void left(double degrees){
  digitalWrite(right_dir_pin, LOW);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, 255);
  analogWrite(left_enable_pin, 255);
  delay(getDurFromDeg(degrees));
}

double getDurFromDeg(double deg){

  return 1000000;
}

double degToRads(double degs){
  return M_PI/180.0 * degs;
}

double radsToDeg(double rads){
  return rads / M_PI * 180;
}

double degSin(double angle){
  return sin(degToRads(angle));
}

double degCos(double angle){
  return cos(degToRads(angle));
}

double getWallLen(double d1, double d2, double angle){
  return sqrt(pow(d2, 2) + pow(d1, 2) - 2*d2*d1*degCos(angle));
}

double getAngle(double d1, double d2, double angle){
  double c = getWallLen(d1, d2, angle);
  double numer = pow(d1, 2) - pow(c, 2) - pow(d2, 2);
  double denom = -2 * c * d2;
  double output = numer / denom;
  output = max(-1.0, min(1.0, output));
  return radsToDeg(acos(output));
}

