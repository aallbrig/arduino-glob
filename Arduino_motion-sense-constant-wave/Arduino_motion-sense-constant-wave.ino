// Motion Sensor
const int motionSensor = 1;
// LED lights (6 total)
const int greenLed     = 9;
const int yellowLed    = 10;
const int redLed1      = 11;
const int redLed2      = 12;
const int redLed3      = 13;
const int waitTime     = 500;
const int quickWait    = 500;
// Servo
#include <Servo.h>
Servo servo;
const int servoPin     = 2;
int pos                = 0;
const int servoStartDegree   = 100;
const int servoEndDegree     = 140;
// LCD Display
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

void setup(){
  // Servo setup
  servo.attach(servoPin);
  servo.write(servoStartDegree);
  // LED setup
  // pinMode(motionSensor, INPUT);
  // pinMode(greenLed, OUTPUT);
  // pinMode(yellowLed, OUTPUT);
  // pinMode(redLed1, OUTPUT);
  // pinMode(redLed2, OUTPUT);
  // pinMode(redLed3, OUTPUT);
  // Define LCD Display
  // lcd.begin(16, 2);
  // any one-time tests
  /*testLcdDisplay();*/
  // servo.write(45);
  // testServo();
}
void testServo(){
 for(pos = 0; pos < 180; pos += 1){
    servo.write(pos);
    delay(50);
  } 
  servo.write(0);
  delay(10000);
}
void testLeds(){
  // Test LED lights
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed1, HIGH);
  resetLeds();
}
void testLcdDisplay(){
  // set up the LCD's number of columns and rows: 
  lcd.clear();
  lcd.home();
  // Print a message to the LCD.
  lcd.setCursor(4, 0);
  lcd.print("Hello,");
  lcd.setCursor(5, 1);
  lcd.print("Dave...");
  delay(waitTime);
}
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
  servo.write(servoEndDegree);
  lcd.home();
  lcd.clear();
  lcd.home();
  // Print a message to the LCD.
  lcd.setCursor(4, 0);
  lcd.print("Hello,");
  lcd.setCursor(5, 1);
  lcd.print("Dave...");
  
  digitalWrite(redLed1, HIGH);
  digitalWrite(greenLed, LOW);
  delay(waitTime/3);
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
  
  servo.write(servoStartDegree);
  lcd.clear(); 
}
void routineTwo() {
  resetLeds();
  servo.write(10);
  delay(100);
  servo.write(servoStartDegree);
  delay(100);
}
void onMotionSense(){
  routineOne();
  /*routineTwo();*/
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
  /*testServo();*/
  /*testLeds();*/
  /*testLcdDisplay();*/
}

