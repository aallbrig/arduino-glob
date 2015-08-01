// LCD screen
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Range Finder
#define trigPin 3
#define echoPin 2
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

// Fun stuff
int count = 0;

void setup(){
  // Define LCD Display
  lcd.begin(16, 2);
  lcd.write("Begin");

  // Range finder
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  // lcd.clear();
  if(not digitalRead(A0)){
    // lcd.write("Pushing A0");
    takeRangeReading();
    delay(500);
  }
  //Delay 50ms before next reading.
  // delay(1000);
}

void takeRangeReading() {
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */ 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 

   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10); 
   
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   
   //Calculate the distance (in cm) based on the speed of sound.
   distance = duration/58.2;
   
   if (distance >= maximumRange || distance <= minimumRange){
     /* Send a negative number to computer and Turn LED ON 
     to indicate "out of range" */
     lcd.clear();
     lcd.write("Out of range");
   }
   else {
     /* Send the distance to the computer using Serial protocol, and
     turn LED OFF to indicate successful reading. */
     Serial.println(distance);
     lcd.clear();
     lcd.print(String(distance) + " cm");
     if(distance < 10){
        count += 1;
      }
   }
  lcd.setCursor(0, 1);
  lcd.print(String(count) + " under 10cm.");
}