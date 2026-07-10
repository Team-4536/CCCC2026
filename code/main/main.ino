const int right_enable_pin = 6;
const int right_dir_pin = 7;
const int left_enable_pin = 8;
const int left_dir_pin = 9;
const int LED_PIN = 13;
const int LED_PIN_2 = 18;
const int ECHO_PIN = 27;
const int TRIGGER_PIN = 26;

double getSonicDist();

void setup()
{
  // put your setup code here, to run once:
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, 255);
  Serial.begin(9600);
}

void loop()
{

  analogWrite(left_enable_pin, 255);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN_2, LOW);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(500);
  analogWrite(left_enable_pin, LOW);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN_2, HIGH);
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(500);
  Serial.print("Distance (cm): ");
  Serial.println(getSonicDist());
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

  double distance = duration / 58.0; // Calc distance = duration / speed_of_sound (cm/us)

  Serial.print(distance);
  Serial.println("cm");

  return distance;
}