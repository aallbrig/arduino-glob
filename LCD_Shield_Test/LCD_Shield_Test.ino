#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Motion Sensor
const int motionSensor = 12;
int count = 0;
// LED lights (5 total)
const int greenLed     = A5;
const int yellowLed    = A4;
const int redLed1      = 2;
const int redLed2      = A2;
const int redLed3      = A1;
const int waitTime     = 3000;
const int quickWait    = 500;
// Servo (2 total)
#include <Servo.h>
Servo servo1;
Servo servo2;
const int servoPin1     = 11;
const int servoPin2     = 3;
const int servoStartDegree   = 50;
const int servoEndDegree     = 90;

void setup(){
  Serial.begin(9600);
  // Define LCD Display
  lcd.begin(16, 2);
  lcd.write("Shiva Marina");
  // LED setup
  pinMode(greenLed,  OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed1,   OUTPUT);
  pinMode(redLed2,   OUTPUT);
  pinMode(redLed3,   OUTPUT);
  // Servo setup
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(servoStartDegree);
  servo2.write(servoStartDegree);
}

void loop(){
  if(digitalRead(motionSensor) == HIGH){
    lcd.clear();
    lcd.write("Motion detected!");
    lcd.setCursor(0,1);
    count = count + 1;
    // lcd.print(count);
    // digitalWrite(greenLed, HIGH);
    // digitalWrite(yellowLed, HIGH);
    // digitalWrite(redLed1, HIGH);
    // digitalWrite(redLed2, HIGH);
    // digitalWrite(redLed3, HIGH);
    // servo1.write(servoEndDegree);
    // servo2.write(servoEndDegree);
    // delay(1000);
    // digitalWrite(greenLed, LOW);
    // digitalWrite(yellowLed, LOW);
    // digitalWrite(redLed1, LOW);
    // digitalWrite(redLed2, LOW);
    // digitalWrite(redLed3, LOW);
    routineOne();
    lcd.clear();
    lcd.write("Normal...");
    servo1.write(servoStartDegree);
    servo2.write(servoStartDegree);
    delay(1000);
  }
}

// Supporting Functions
void resetLeds(){
  digitalWrite(redLed1, LOW);
  digitalWrite(redLed2, LOW);
  digitalWrite(redLed3, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
}

void routineOne() {
 /* light pattern */
  resetLeds();
  servo1.write(servoEndDegree);
  
  digitalWrite(redLed1, HIGH);
  digitalWrite(greenLed, LOW);
  delay(waitTime/3);
  servo2.write(servoEndDegree);
  digitalWrite(yellowLed, HIGH);
  delay(50);
  digitalWrite(yellowLed, LOW);
  delay(50);
  digitalWrite(yellowLed, HIGH);
  delay(50);
  digitalWrite(yellowLed, LOW);
  delay(50);
  digitalWrite(yellowLed, HIGH);
  delay(50);
  digitalWrite(yellowLed, LOW);
  servo2.write(servoStartDegree);
  delay(waitTime);
  digitalWrite(greenLed, HIGH);
  delay(waitTime);
  //digitalWrite(redLed1, LOW);
  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(redLed1, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
  
  servo1.write(servoStartDegree);
  lcd.clear(); 
}