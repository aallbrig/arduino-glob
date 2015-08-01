#include <SimpleTimer.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <functional>

// Timer
SimpleTimer timer;

// Motion Sensor (PIR)
const int motionSensor = 4;

// LEDs
#define redLedEye 11
#define bottomGreenLed 5
#define bottomYellowLed 3
#define topRedLed 7
#define topYellowLed 6
int leds[] = {
  redLedEye,
  bottomGreenLed,
  bottomYellowLed,
  topRedLed,
  topYellowLed
};

// Servos
#define servo1Pin 10
#define servo2Pin 12

// Text to speech module.
#define rxPin   8  // Serial input (connects to Emic 2's SOUT pin)
#define txPin   9  // Serial output (connects to Emic 2's SIN pin)
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

// char phrases[] = {};

void setup () {
  // Setup leds-- the lazy way
  for (int i = 0; i < sizeof(leds) - 1; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(motionSensor, INPUT);
  // reset LEDs;
  resetLeds();

  // Set up text-to-speech module
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  emicSerial.begin(9600);  
  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully
    initialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it
    to send a ":"
  */
  emicSerial.print('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();                 // Flush the receive buffer

  // best HAL 9000 voice.
  emicSerial.print('N');
  emicSerial.print('4');   // 4 7 8
  emicSerial.print('\n');

  startupAnimation();
}

void loop () {
  timer.run();
}

// Helper functions

void startupAnimation () {
  // Startup sequence for the lulz
  for(int i = 0; i < 255; i++){
    analogWrite(redLedEye, i);
    timer.setTimeout(5 * i, std::bind(&analogWrite, i));
  }
  // digitalWrite(redLedEye, HIGH);
  // emicSerial.print("SHello I am Hal 9000.\n");
  // delay(3200);
  // digitalWrite(bottomGreenLed, HIGH);
  // emicSerial.print("SStarting bootup sequence now. Please wait. Beep beep boop.\n");
  // delay(7000);
  // digitalWrite(bottomGreenLed, LOW);
  // digitalWrite(topYellowLed, HIGH);
  // digitalWrite(bottomYellowLed, HIGH);
  // emicSerial.print("SBoop boop. Beep. beep.\n");
  // delay(4000);
  // resetLeds();
  // digitalWrite(topRedLed, HIGH);
  // emicSerial.print("SWarning! Error. Sentience defrag requested\n");
  // delay(5500);
  // digitalWrite(redLedEye, HIGH);
  // emicSerial.print("SI feel. Funny. he he he. he he.\n");
  // delay(6000);
  // emicSerial.print("SWould you like me to shave your dog?\n");
  // delay(4000);
  // resetLeds();
}

void resetLeds () {
  for (int i=0; i < sizeof(leds) - 1; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void onMotionSenseAnimation () {
  
}

void onIdleAnimation () {
  
}