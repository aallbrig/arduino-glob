/* This program turns on the KY-008 Laser Transmitter Module and varies the output
intensity using PWM on digital pin 9
*/

const int ledPin = 11;
const int pirPin = 4;
int delay_val = 500;
int led_on = 1000;
bool pirRead = LOW;

void setup()
{
  Serial.begin(1200);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
}

void loop()
{
  Serial.println("\n\nHAL 9000 module");
  
  
  delay(2000);
  pirRead = digitalRead(pirPin);
  Serial.println(pirRead);
  digitalWrite(ledPin, pirRead);
  delay(2000);
  digitalWrite(ledPin, LOW);
  // if(pirRead == HIGH) {
  //   digitalWrite(ledPin, HIGH);
  //   delay(led_on);
  //   digitalWrite(ledPin, LOW);
  //   delay(delay_val);
  // }
}