#include "Timer.h"                     //http://github.com/JChristensen/Timer
// Pin mapping
#define ledPin1 6
#define ledPin2 5
#define ledPin3 7
// Handy macro
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )
Timer t;

char* phrases[] = {
  "Hello I am hal 9000.",
  "Pleased to meet you.",
  "How is that coffee today?",
  "How about that baseball."
};

void printLn () {
  static int phrasesIndex = 0;
  if (phrasesIndex >= arr_len(phrases) - 1) {
    phrasesIndex = 0;
  }
  // HAL say some sequence.
  Serial.println("......Index #" + String(phrasesIndex) + "....");
  Serial.println(phrases[++phrasesIndex]);
  Serial.println(String(arr_len(phrases) - 1));
  Serial.println(String(phrasesIndex));
}

void setup () {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  int led1Event = t.oscillate(ledPin1, 1000, HIGH);
  int led2Event = t.oscillate(ledPin2, 100, HIGH);
  int led3Event = t.oscillate(ledPin3, 10000, HIGH);
  t.every(1000, printLn, arr_len(phrases) - 1);
  // t.after(10000, turnOff);
}

void loop () {
  t.update();
}