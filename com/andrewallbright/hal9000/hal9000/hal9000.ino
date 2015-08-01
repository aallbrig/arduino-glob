class Hal9000
{
  public:
    Hal9000();
    void greet();
  private:
    int _pin;
};

// Motion Sensor
const int motionSensor = 2;
volatile boolean motionSense = false;

// LCD screen
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// LED lights (5 total)
const int greenLed     = 11;
const int yellowLed    = A3;
const int redLed1      = 12;
const int redLed2      = A2;
const int redLed3      = A1;
const int waitTime     = 3000;
const int quickWait    = 500;

// Servo (2 total)
#include <Servo.h>
Servo servo;
const int servoPin1     = 13;
const int servoPin2     = 13;
const int servoStartDegree   = 50;
const int servoEndDegree     = 90;

void setup(){
  // Motion Sensor
  //attachInterrupt(0, onMotionInterrupt, RISING);

  // Define LCD Display
  lcd.begin(16, 2);
  lcd.write("Bananas");
  
  // any one-time tests
  /*testLcdDisplay();*/
  digitalWrite(greenLed, 1);
  digitalWrite(yellowLed, 1);
  // Servo setup
  servo.attach(servoPin1);
  servo.write(servoStartDegree);
}

void loop(){
  if (digitalRead(motionSensor) == HIGH) {
    motionSense = true;
    Serial.println("onMotionSense()");
  } else {
    Serial.println("onIdle()");
  }
  if(motionSense){
    lcd.clear();
    lcd.print("Interrupt detected");
    servo.write(servoStartDegree);
    delay(500);
    lcd.clear();
    servo.write(servoEndDegree);
    delay(500);
    // digitalWrite(greenLed, LOW);
    // digitalWrite(yellowLed, LOW);
    motionSense = false;
  }
}
