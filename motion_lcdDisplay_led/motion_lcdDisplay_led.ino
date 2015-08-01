#include <LiquidCrystal.h>
// Se
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Motion Sensor
const int motionSensor = 2;
// LED lights (6 total)
const int greenLed     = 5;
const int yellowLed    = 7;
const int redLed1      = 9;
const int redLed2      = 11;
const int redLed3      = 13;
const int waitTime     = 3000;
const int quickWait    = 500;

void setup(){
  pinMode(motionSensor, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(redLed3, OUTPUT);
  
  // Test LED lights
  /*digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed1, HIGH);*/
}
void resetLeds(){
  digitalWrite(redLed1, LOW);
  digitalWrite(redLed2, LOW);
  digitalWrite(redLed3, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
}
void onMotionSense(){
  /*digitalWrite(redLed3, HIGH);
  delay(100);
  digitalWrite(redLed3, LOW);
  digitalWrite(redLed2, HIGH);
  delay(100);
  digitalWrite(redLed2, LOW);*/
  resetLeds();
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, HIGH);
  delay(waitTime);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed1, HIGH);
  delay(waitTime);
  digitalWrite(redLed1, LOW);
  digitalWrite(greenLed, HIGH);
  delay(waitTime);
  digitalWrite(greenLed, LOW);
}
void onIdle(){
  digitalWrite(redLed1, LOW);
  digitalWrite(redLed2, LOW);
  digitalWrite(redLed3, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  delay(quickWait);
  digitalWrite(redLed3, LOW);
  digitalWrite(redLed2, HIGH);
  delay(quickWait);
}

void loop(){
  int value = digitalRead(motionSensor);
  if (value == HIGH) {
    onMotionSense();
  } else {
    onIdle();
  }
}

