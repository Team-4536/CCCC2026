const int right_enable_pin = 6;
const int right_dir_pin = 7;
const int left_enable_pin = 8;
const int left_dir_pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);

  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);

}

void loop() {

  analogWrite(right_enable_pin, 255);
  analogWrite(left_enable_pin, 255);
  delay(1000);
  analogWrite(right_enable_pin, LOW);
  analogWrite(left_enable_pin, LOW);
  delay(1000);

}