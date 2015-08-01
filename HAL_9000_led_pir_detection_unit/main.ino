// Motion Sensor (PIR)
const int pirRead = 8;
// volatile boolean motionSense = false;
// LEDs
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
const int led4 = 12;
const int led5 = 13;

void setup(){
  // setup Arduino Serial Monitor
  Serial.begin(9600);
  // while (!Serial);   // wait until ready
  Serial.println("\n\nHAL 9000 module");
  // Serial.flush();

  pinMode(led1, OUTPUT);
  pinMode(pirRead, INPUT);
  // pinMode(6, OUTPUT);
  // digitalWrite(6, HIGH);
  // pinMode(7, OUTPUT);
  // digitalWrite(7, HIGH);
  // pinMode(8, OUTPUT);
  // digitalWrite(8, HIGH);
  // Motion Sensor
  // attachInterrupt(0, onMotionInterrupt, RISING);

  // any one-time tests
  /*testLcdDisplay();*/
}

void loop(){
  // delay(5 * 60 * 1000); // 5 seconds
  Serial.println("Start of loop!");
  // int value = digitalRead(pirRead);
  if (digitalRead(pirRead)) {
    Serial.println("onMotionSense()");
    digitalWrite(led1, LOW);
    delay(500);
    digitalWrite(led1, HIGH);
    delay(500);
  } else { /* Serial.println("onIdle()"); */ }
  // digitalWrite(led, LOW);
  // delay(500);
  // digitalWrite(led, HIGH);
  // delay(500);

  // if(motionSense){
  //   lcd.clear();
  //   lcd.print("Interrupt detected");
  //   delay(1000);
  //   lcd.clear();
  //   motionSense = false;
  // }
}

/*** SUPPORTING FUNCTIONS ***/

// void onMotionInterrupt() {
//   motionSense = true;
// }
