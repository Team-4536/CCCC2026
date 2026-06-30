

const int right_enable_pin = 6;
const int right_dir_pin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);

  digitalWrite(right_dir_pin, HIGH);

}

void loop() {

  digitalWrite(right_enable_pin, HIGH);
  delay(1000);
  digitalWrite(right_enable_pin, LOW);
  delay(1000);

}