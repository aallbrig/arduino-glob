// Motion Sensor (PIR)
const int motionSensor = 4;

// LEDs
const int redLedEye = 11;
const int bottomGreenLed = 5;
const int bottomYellowLed = 3;
const int topRedLed = 7;
const int topYellowLed = 6;
int leds[] = {
  redLedEye,
  bottomGreenLed,
  bottomYellowLed,
  topRedLed,
  topYellowLed
};

// Animation states
boolean isOnIdleAnimationPlaying = false;
boolean isOnMotionAnimationPlaying = false;

// Text to speech module.
// include the SoftwareSerial library so we can use it to talk to the Emic 2 module
// include the SoftwareSerial library so we can use it to talk to the Emic 2 module
#include <SoftwareSerial.h>
#define rxPin   8  // Serial input (connects to Emic 2's SOUT pin)
#define txPin   9  // Serial output (connects to Emic 2's SIN pin)
// #define ledPin  13  // Most Arduino boards have an on-board LED on this pin
// set up a new serial port
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);
// char phrases[] = {};

// Servo modules.

// Time keeping
long previousMillis = 0;

void setup () {
  // Serial.begin(9600);
  // Serial.println("\n\nHAL 9000 module");

  // pinMode(redLedEye, OUTPUT);
  // Setup leds-- the lazy way
  for (int i = 0; i < sizeof(leds) - 1; i++) {
    pinMode(leds[i], OUTPUT);
  }

  pinMode(motionSensor, INPUT);
  // reset LEDs;
  resetLeds();

  // Set up text-to-speech module here.
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // set the data rate for the SoftwareSerial port
  emicSerial.begin(9600);

  // digitalWrite(ledPin, LOW);  // turn LED off
  
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
  emicSerial.print('8');   // 4 7 8
  emicSerial.print('\n');

  // Initial staet of animation is idle is playing (woo!);
  isOnIdleAnimationPlaying = true;

  startupAnimation();
}

void loop () {
  // emicSerial.print("SI am Hal 9000.\n");
  // delay(3000);
  // emicSerial.print("SHello how are you doing?\n");  // Send the desired string to convert to speech
  // delay(30000);

  // Figure out wether to take a motion reading and modify application state.
  if (isOnMotionAnimationPlaying) {
    // Serial.println("isOnMotionAnimationPlaying is already playing! Do nothing");
  } else {
    // Serial.println("Motion animation isn't playing-- time to read motion sensor");
    if (digitalRead(motionSensor)) {
      // Serial.println("Successful detection!  Switching states!");
      
      resetLeds();
      turnOnMotionAnimationState();
    }
  }

  // Figure out which "animation" to play.
  if (isOnMotionAnimationPlaying) {
    onMotionSenseAnimation();
  } else if (isOnIdleAnimationPlaying) {
    onIdleAnimation();
  } else {
    // Serial.println("I have no idea how we got here... Resetting shinanigans");
    
    resetLeds();
    turnOnIdleAnimationState();
  }
}

// Helper functions

void startupAnimation () {
  // Startup sequence for the lulz
  for(int i = 0; i < 255; i++){
    analogWrite(redLedEye, i);
    delay(5);
  }
  digitalWrite(redLedEye, HIGH);
  emicSerial.print("SHello I am Hal 9000.\n");
  delay(3200);
  digitalWrite(bottomGreenLed, HIGH);
  emicSerial.print("SStarting bootup sequence now. Please wait. Beep beep boop.\n");
  delay(7000);
  digitalWrite(bottomGreenLed, LOW);
  digitalWrite(topYellowLed, HIGH);
  digitalWrite(bottomYellowLed, HIGH);
  emicSerial.print("SBoop boop. Beep. beep.\n");
  delay(4000);
  resetLeds();
  digitalWrite(topRedLed, HIGH);
  emicSerial.print("SWarning! Error. Sentience defrag requested\n");
  delay(5500);
  digitalWrite(redLedEye, HIGH);
  emicSerial.print("SI feel. Funny. he he he. he he.\n");
  delay(6000);
  emicSerial.print("SWould you like me to shave your dog?\n");
  delay(4000);
  resetLeds();
}

void resetLeds () {
  for (int i=0; i < sizeof(leds) - 1; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void turnOnIdleAnimationState () {
  isOnIdleAnimationPlaying = true;
  isOnMotionAnimationPlaying = false;
}

void turnOnMotionAnimationState () {
  isOnIdleAnimationPlaying = false;
  isOnMotionAnimationPlaying = true;
}

void onMotionSenseAnimation () {
  unsigned long currentMillis = millis();
  
  resetLeds();

  delay(500);
  // digitalWrite(redLedEye, HIGH);
  // digitalWrite(bottomYellowLed, HIGH);
  // digitalWrite(bottomGreenLed, HIGH);
  for (int i = 0; i < sizeof(leds) - 1; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(500);

  turnOnIdleAnimationState();
  resetLeds();
}

void onIdleAnimation () {
  unsigned long currentMillis = millis();
}