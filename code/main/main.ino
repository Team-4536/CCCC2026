const int ECHO_PIN = 27;
const int TRIGGER_PIN = 26;

double getSonicDist();

void setup()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}

void loop()
{
  Serial.print("Distance (cm): ");
  Serial.println(getSonicDist());
  delay(500);
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
  return obstacleDist < AVOID_DIST
}

void forward(int speed)
{
  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, speed);
  analogWrite(left_enable_pin, speed);
}

void right()
{
  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, 255);
  analogWrite(left_enable_pin, LOW);
}