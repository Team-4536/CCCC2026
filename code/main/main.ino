// Wiring Test
// This program will teach you how to blink an LED.

int LED_Pin_13 = 13;
int LED_Pin_18 = 18;

void setup()
{
  pinMode(LED_Pin_13, OUTPUT);
  pinMode(LED_Pin_18, OUTPUT);
}
void loop()
{
  digitalWrite(LED_Pin_13, HIGH);
  digitalWrite(LED_Pin_18, HIGH);
  delay(1000);
  digitalWrite(LED_Pin_13, LOW);
  digitalWrite(LED_Pin_18, LOW);
  delay(1000);
}
