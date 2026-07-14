int LED_Pin = 13;
int right_Motor = 7;
int right_Motor_Dir = 6;
int left_Motor = 9;
int left_Motor_Dir = 8; 
int echo_pin = 27;
int trig_pin = 26;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_Pin, OUTPUT);
  pinMode(right_Motor, OUTPUT);
  pinMode(right_Motor_Dir, OUTPUT);
  pinMode(left_Motor, OUTPUT);
  pinMode(left_Motor_Dir, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);

  digitalWrite(right_Motor_Dir, LOW);
  digitalWrite(left_Motor_Dir, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trig_pin, LOW);
  delay(20);
  digitalWrite(trig_pin, HIGH); // Ultrasonic sensor makes a sound waves
  delay(20);
  digitalWrite(trig_pin, LOW);
  long return_time = pulseIn(echo_pin, HIGH); 
  // Get the time it takes to hear the sound wave bounce back

  float distance_cm = (return_time * 0.0343)/2;
  if (distance_cm < 50) {
	analogWrite(right_Motor, 255); // This turns the right motor off
	analogWrite(left_Motor, 0); // This turns the left motor off
  digitalWrite(LED_Pin, HIGH);
  }

  else {
	analogWrite(right_Motor, 255); // This turns the right motor on
	analogWrite(left_Motor, 255);
  digitalWrite(LED_Pin, LOW); // This turns the left motor on
  }

  Serial.println(distance_cm);

}
