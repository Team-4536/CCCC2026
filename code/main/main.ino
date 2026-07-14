int right_enable_pin = 6;
int right_dir_pin = 7;
int left_enable_pin = 8;
int left_dir_pin = 9;

void setup()
{

  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);

  digitalWrite(right_dir_pin, HIGH);
  digitalWrite(left_dir_pin, HIGH);

  digitalWrite(right_enable_pin, HIGH);
}

void loop()
{

  digitalWrite(left_enable_pin, HIGH);
  delay(1000);
  digitalWrite(left_enable_pin, LOW);
  delay(1000);
}