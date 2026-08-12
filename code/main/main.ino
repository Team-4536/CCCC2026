// #define _USE_MATH_DEFINES
// #include <cmath>

const int right_enable_pin = 7;
const int right_dir_pin = 6;
const int left_enable_pin = 9;
const int left_dir_pin = 8;
const int LED_PIN = 13;
const int ECHO_PIN = 27;
const int TRIGGER_PIN = 26;

double getSonicDist(bool doDelay = false, int reads = 1);
double readWallDist(); // getSonicDist but with a loop that can turn if it gets no good reads
bool obstacleAhead();
void forward(int speed);
void right(double degrees);
void left(double degrees);
double getDurFromDeg(double deg);
double getAngle(double d1, double d2, double angle);
double getWallLen(double d1, double d2, double angle);
void stop();

double dist1;
double dist2;
double wallLen;
double errorAngle;

const double MAX_MEASURE = 40;                          // maximum distance (cm) from ultrasonic I will use for trig
const double DIST_FROM_CENTER_OF_ROT = 1;              // in cm
const double AVOID_DIST = 10 + DIST_FROM_CENTER_OF_ROT; // in cm
const double TURN_ANGLE = 15;                           // in degrees
const double SPEED_RATIO = 90/100.0; // How fast the right motor turns in relation to the left 

const int TRIALS = 1;
const int TRIAL_SCALAR = 1; // multiply fullr rot time by this
const double TIMES_360[TRIALS] = {1.54}; // in seconds
double FULL_ROT_TIME; // in ms
double actualAngle;

void setup()
{
  // put your setup code here, to run once:
  double sum = 0;

  for (double time : TIMES_360)
  {
    sum += time * 1000; // convert to ms
  }
  FULL_ROT_TIME = sum / TRIALS * TRIAL_SCALAR;

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
  // Serial.print("Loop 1: ");
  dist1 = getSonicDist();

  if (dist1 == -1)
  {
    dist1 = 800;
  }
  // delay(500);
  if (obstacleAhead())
  {
    Serial.println("Obstacle");
    stop();
    Serial.println("Reading First: ");
    dist1 = readWallDist();
    Serial.println(dist1);

    Serial.println("Turning");
    right(TURN_ANGLE);

    Serial.println("Reading Second: ");
    dist2 = readWallDist();
    Serial.println(dist2);

    wallLen = getWallLen(dist1, dist2, actualAngle);
    errorAngle = getAngle(dist1, dist2, actualAngle);

    Serial.print("Turning: ");
    
    if (errorAngle > 90)
    {
      left(180 - errorAngle);
      Serial.print(180 - errorAngle);
      Serial.println(" Degs Left");
    }
    else
    {
      right(errorAngle);
      Serial.print(errorAngle);
      Serial.println(" Degs Right");
    }
  }
  else
  {
    forward(255);
  }
}

double getSonicDist(bool doDelay, int reads)
{ // Contains code from the big DJ Orser

  // Measure pulse width on echoPin
  double currDur;
  double currDist;
  double sum = 0;
  int goodReads = 0;

  for (int i = 0; i < reads; i++)
  {
    // Send a HIGH Pulse to triggerPin that is 10us Long
    digitalWrite(TRIGGER_PIN, LOW);  // Trigger should already be low, just in case
    delayMicroseconds(2);            // This is just like delay() but in microseconds
    digitalWrite(TRIGGER_PIN, HIGH); // set HIGH
    delayMicroseconds(10);           // wait 10us
    digitalWrite(TRIGGER_PIN, LOW);  // set LOW
    if (doDelay)
    {
      currDur = pulseIn(ECHO_PIN, HIGH);
    }
    else
    {
      currDur = pulseIn(ECHO_PIN, HIGH, 50000);
    }

    currDist = currDur / 58.0; // Calc distance duration / speed_of_sound (cm/us)

    if ((currDist != 0 && currDist < MAX_MEASURE))
    {
      sum += currDist;
      goodReads++;
    }
  }
  double avgDistance = sum / goodReads;
  // Serial.print(distance);
  // Serial.println(" cm");

  if (goodReads <= 0)
  {
    return -1;
  }

  return avgDistance + DIST_FROM_CENTER_OF_ROT;
}

double readWallDist()
{
  double dist;
  for (int i = 0; i < 3; i++)
  {
    dist = getSonicDist(true, 10);

    if (dist < 0)
    {
      Serial.println("Bad Read, correcting");

      double angle = 5;
      actualAngle = TURN_ANGLE - 5 * (i + 1);

      if (i == 2)
      {
        angle = 10; // prevents it from reading the same angle and trying to do math that won't work
        actualAngle = -5;
      }

      left(angle);
    } 
    else
    {
      actualAngle = TURN_ANGLE;
      return dist;
    }
  }
  Serial.println("Couldn't get a read");
  return -1; // sads
}
bool obstacleAhead()
{
  Serial.print("YO: ");
  Serial.println(dist1);
  return dist1 < AVOID_DIST;
}

void forward(int speed)
{
  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, speed);
  analogWrite(left_enable_pin, speed * SPEED_RATIO);
}

void right(double degrees)
{
  if (degrees < 0)
  {
    left(abs(degrees));
    return;
  }

  digitalWrite(right_dir_pin, LOW);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, 255);
  analogWrite(left_enable_pin, 255 * SPEED_RATIO);
  delay(getDurFromDeg(degrees));
  stop();
}

void left(double degrees)
{
  if (degrees < 0)
  {
    right(abs(degrees));
    return;
  }

  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, LOW);
  analogWrite(right_enable_pin, 255);
  analogWrite(left_enable_pin, 255 * SPEED_RATIO);
  delay(getDurFromDeg(degrees));
  stop();
}

void stop()
{
  analogWrite(right_enable_pin, 0);
  analogWrite(left_enable_pin, 0);
}

double getDurFromDeg(double deg)
{

  //return FULL_ROT_TIME * deg / 360;
  if(deg <= 0){
    return 0;
  }

  double s = ((3.69868 * pow(10, -8)) * pow(deg, 3)) - (0.000020899 * pow(deg, 2)) + (0.0067108 * deg) + 0.00696383;
  return s * 1000;
}

double degToRads(double degs)
{
  return M_PI / 180.0 * degs;
}

double radsToDeg(double rads)
{
  return rads / M_PI * 180;
}

double degSin(double angle)
{
  return sin(degToRads(angle));
}

double degCos(double angle)
{
  return cos(degToRads(angle));
}

double getWallLen(double d1, double d2, double angle)
{
  return sqrt(pow(d2, 2) + pow(d1, 2) - 2 * d2 * d1 * degCos(angle));
}

double getAngle(double d1, double d2, double angle)
{
  double c = getWallLen(d1, d2, angle);
  double numer = pow(d1, 2) - pow(c, 2) - pow(d2, 2);
  double denom = -2 * c * d2;
  double output = numer / denom;
  output = max(-1.0, min(1.0, output));
  return radsToDeg(acos(output));
}
