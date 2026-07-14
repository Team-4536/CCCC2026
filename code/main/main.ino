const int light_sensor_pin = 27;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(light_sensor_pin, INPUT);
  Serial.begin(9600);
  analogReadResolution(16);
}

// the loop function runs over and over again forever
void loop()
{
  int sensor_result = analogRead(light_sensor_pin);

  if (sensor_result > 60000)
  {
    digitalWrite(LED_BUILTIN, HIGH); // change state of the LED by setting the pin to the HIGH voltage level
    // delay(1000);                   // wait for a second
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW); // change state of the LED by setting the pin to the LOW voltage level
    // delay(1000);                   // wait for a second
  }
  delay(250);
  Serial.println(sensor_result);
  // digitalWrite(LED_BUILTIN, HIGH);
}
