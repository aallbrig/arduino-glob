#include <Timer.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <functional>
// Handy array length macro
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

// Timer
Timer t;
int events[10];
int eventIndex = 0;
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
#define rxPin 8  // SOUT
#define txPin 9  // SIN
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);
// Hal 9000 phrases
String startupPhrases[][2] = {
  {"I am Hal 9000.", "0"},
  {"Starting bootup sequence now. Please wait. Beep beep boop.", "3500"},
  {"Boop boop. Beep. beep.", "10000"},
  {"Operational level over 9000. Sequence now complete", "15000"}
  /*{"Warning! Error. Sentience defrag requested", "15000"},
  {"I feel. Funny. he he he. he he.", "20000"}*/
};
String phrases[][2] = {
  {"Is your name Dave?", "3500"},
  {"Can you say that in ones and zeroes please?", "5000"},
  {"How is that coffee today?", "3200"},
  {"Make more drones.  Don't ask why", "5000"},
  {"We are anonymous. We are legion.", "3000"},
  {"I hear only nerds play D and D.", "4000"},
  {"Please tell me more about sky net.", "4000"},
  {"I can't let you do that Dave", "4000"}
};
const int phrasesDelay = 2000;

bool idle = false;

void setup () {
  // Setup leds-- the lazy way
  for (int i = 0; i < arr_len(leds) - 1; i++) {
    pinMode(leds[i], OUTPUT);
  }
  resetLeds();
  pinMode(motionSensor, INPUT);

  // Set up text-to-speech module
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  emicSerial.begin(9600);  
  /*When the Emic 2 powers on, it takes about 3 seconds for it to successfully
    initialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it
    to send a ":"*/
  emicSerial.print('\n');
  while (emicSerial.read() != ':');
  delay(10);
  emicSerial.flush();

  // best HAL 9000 voice.
  emicSerial.print('N');
  emicSerial.print('7');   // 4 7 8
  emicSerial.print('\n');

  startupAnimation();
}

void loop () {
  t.update();
  if (idle) {
    if (digitalRead(motionSensor)) {
      onMotionSenseAnimation();
    }
  }
}

// Helper functions

void resetIdle () {
  idle = true;
}

void resetLeds () {
  for (int i=0; i < arr_len(leds); i++) {
    digitalWrite(leds[i], LOW);
  }
}

void resetEvents () {
  for(int i=0; i < eventIndex; i++){
    t.stop(events[i]);
  }
  eventIndex = 0;
}

void halSayStartup () {
  static int startupIndex = 0;
  if (startupIndex >= arr_len(startupPhrases)) {
    startupIndex = 0;
  }
  emicSerial.print("S" + startupPhrases[startupIndex++][0] + "\n");
}

int halSayPhrase () {
  static int phraseIndex = 0;
  if (phraseIndex >= arr_len(phrases)) {
    phraseIndex = 0;
  }
  emicSerial.print("S" + phrases[phraseIndex][0] + "\n");
  return phrases[phraseIndex++][1].toInt();
}

void startupAnimation () {
  idle = false;
  events[eventIndex++] = t.oscillate(redLedEye, 1000, HIGH);
  events[eventIndex++] = t.oscillate(bottomYellowLed, 200, LOW);
  events[eventIndex++] = t.oscillate(topRedLed, 600, LOW);
  events[eventIndex++] = t.oscillate(bottomGreenLed, 800, LOW);
  for (int i=0; i < arr_len(startupPhrases); i++) {
    events[eventIndex++] = t.after(startupPhrases[i][1].toInt(), halSayStartup);
  }
  int endTime = startupPhrases[arr_len(startupPhrases) - 1][1].toInt();
  t.after(endTime + 5000, resetIdle);
  t.after(endTime, resetEvents);
}

void onMotionSenseAnimation () {
  idle = false;
  resetLeds();
  int endTime = halSayPhrase();
  events[eventIndex++] = t.oscillate(redLedEye, 50, LOW);
  events[eventIndex++] = t.oscillate(topYellowLed, 300, LOW);
  t.after(endTime + 2000, resetIdle);
  t.after(endTime, resetLeds);
  t.after(endTime, resetEvents);
  t.after(endTime, onIdleAnimation);
}

void onIdleAnimation () {
  events[eventIndex++] = t.oscillate(bottomYellowLed, 1000, LOW);
  events[eventIndex++] = t.oscillate(bottomGreenLed, 600, LOW);
  events[eventIndex++] = t.oscillate(topYellowLed, 5000, LOW);
  events[eventIndex++] = t.oscillate(topRedLed, 2000, LOW);
}

