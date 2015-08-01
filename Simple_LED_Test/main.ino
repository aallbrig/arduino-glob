const int LED = 13;

void setup(){
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop(){
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}