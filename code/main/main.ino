//#define _USE_MATH_DEFINES
//#include <cmath>

const int right_enable_pin = 7;
const int right_dir_pin = 6;
const int left_enable_pin = 9;
const int left_dir_pin = 8;
const int LED_PIN = 13;
const int ECHO_PIN = 27;
const int TRIGGER_PIN = 26;



double getSonicDist(bool doDelay = false);
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

const double DIST_FROM_CENTER_OF_ROT = 17; // in cm
const double AVOID_DIST = 10 + DIST_FROM_CENTER_OF_ROT; // in cm
const double TURN_ANGLE = 15; // in degrees

const int TRIALS = 7;
const double TIMES_360[TRIALS] = {2.84, 3.06, 2.86, 2.56, 2.43, 2.82, 2.65}; // in seconds
double sum = 0;
double FULL_ROT_TIME; // in ms

void setup()
{
  // put your setup code here, to run once:

  for(double time : TIMES_360){
    sum += time * 1000; // convert to ms
  }
  double FULL_ROT_TIME = sum / TRIALS;

  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);

  Serial.print("First: ");
  dist1 = getSonicDist();

}

void loop()
{
  //Serial.print("Loop 1: ");
  dist1 = getSonicDist();
  //delay(500);
  if (obstacleAhead())
  {
    //Serial.println("Obstacle");
    dist1 = getSonicDist(true);
    right(TURN_ANGLE);
    //Serial.print("Loop 2: ");
    dist2 = getSonicDist(true);
    wallLen = getWallLen(dist1, dist2, TURN_ANGLE);
    errorAngle = getAngle(dist1, dist1, TURN_ANGLE);

    if(errorAngle > 90){
      //left(180-errorAngle);
    } else {
      //right(errorAngle);
    }
  }
  else
  {
    forward(255);
  }


}

double getSonicDist(bool doDelay)
{ // Contains code from the big DJ Orser

  // Send a HIGH Pulse to triggerPin that is 10us Long
  digitalWrite(TRIGGER_PIN, LOW);  // Trigger should already be low, just in case
  delayMicroseconds(2);            // This is just like delay() but in microseconds
  digitalWrite(TRIGGER_PIN, HIGH); // set HIGH
  delayMicroseconds(10);           // wait 10us
  digitalWrite(TRIGGER_PIN, LOW);  // set LOW

  double duration = 0; // Measure pulse width on echoPin

  if(doDelay){
    duration = pulseIn(ECHO_PIN, HIGH);
  } else{
    duration = pulseIn(ECHO_PIN, HIGH, 30000);
  }

  if(duration == 0){
    return 400;
  } 
  
  double distance = duration / 58.0; // Calc distance duration / speed_of_sound (cm/us)

  //Serial.print(distance);
  //Serial.println(" cm");

  return distance + DIST_FROM_CENTER_OF_ROT;
}

bool obstacleAhead()
{
  // Serial.print("YO: ");
  // Serial.println(dist1);
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

  return FULL_ROT_TIME * deg/360;
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

