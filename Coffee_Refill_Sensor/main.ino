int photoResistor = A0;  //define a pin for Photo resistor
int photoResistMaxValue = 1023;
int warningLed = 2;
int debugLed = 3;
int smiley[] = {4,5,6,7,8,9,10};
int smileyLedCount = sizeof(smiley);
volatile bool smileyOn = false;
bool switches[] = {false,false,false,false,false,false,false,false,false};


void setup(){
  pinMode(debugLed, OUTPUT);
  pinMode(warningLed, OUTPUT);
  Serial.begin(9600);
  // for(int i=0; i<smileyLedCount; i++){
  //   pinMode(smiley[i], OUTPUT);
  //   digitalWrite(smiley[i], HIGH);
  // }
  digitalWrite(warningLed, HIGH);
  // timer.setInterval(1000, repeatMe);
}

void loop(){
  int val = analogRead(photoResistor);
  Serial.print(val);
  Serial.println();
  Serial.print(val/4);
  Serial.println();
  Serial.println();
  analogWrite(debugLed, val/4);
  if(val < photoResistMaxValue/4){
    digitalWrite(warningLed, HIGH);
    for(int i=0; i<smileyLedCount; i++){
      digitalWrite(smiley[i], HIGH);
    }
    smileyOn = true;
  } else {
    if(digitalRead(warningLed) == HIGH){
      digitalWrite(warningLed, LOW);
    }
    if(smileyOn){
      for(int i=0; i<smileyLedCount; i++){
          digitalWrite(smiley[i], LOW);
      }
      smileyOn = false;
    }
    // if(digitalRead(smiley[0] == HIGH)){
    //   for(int i=0; i<smileyLedCount; i++){
    //     digitalWrite(smiley[i], LOW);
    //   }
    // }
    // digitalWrite(warningLed, LOW);
  }
  // timer.run();
  delay(10); //short delay for faster response to light.
}
