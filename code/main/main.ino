const int right_enable_pin = 6;
const int right_dir_pin = 7;
const int left_enable_pin = 8;
const int left_dir_pin = 9;
const uint LED_PIN = 27;

void setup() {
  // put your setup code here, to run once:
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);
  analogWrite(right_enable_pin, 255);

}

void loop() {

  analogWrite(left_enable_pin, 255);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  analogWrite(left_enable_pin, LOW);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);

}