int right_motor_enable_pin = 6;
int right_motor_dir_pin = 7;
int left_motor_enable_pin = 8;
int left_motor_dir_pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(right_motor_enable_pin, OUTPUT);
  pinMode(right_motor_dir_pin, OUTPUT);
  pinMode(left_motor_enable_pin, OUTPUT);
  pinMode(left_motor_dir_pin, OUTPUT);

  digitalWrite(right_motor_dir_pin, HIGH); // Setting the right motor direction to forward
  digitalWrite(left_motor_dir_pin, HIGH); // Setting the left motor direction to forward

}

void loop() {

  analogWrite(right_motor_enable_pin, 255); // This functions the exact same as a digitalWrite() on HIGH
  analogWrite(left_motor_enable_pin, 255);
  delay(1000);

  analogWrite(right_motor_enable_pin, 0);
  analogWrite(left_motor_enable_pin, 0);
  delay(1000);

}