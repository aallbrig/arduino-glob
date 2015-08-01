// LCD screen
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Temperature Sensor
#define temperatureSensorPin A1

void setup(){
  // Define LCD Display
  lcd.begin(16, 2);
  lcd.write("Begin");

  // Temperature Sensor

}

void loop() {
  if(not digitalRead(A0)){
    takeTemperatureReading();
    delay(500);
  }
}

void takeTemperatureReading() {
  // Taken from https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
  int reading = analogRead(temperatureSensorPin);
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");

  // now convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");
  lcd.clear();
  lcd.print(String(temperatureF) + " F");
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */ 
  //  digitalWrite(trigPin, LOW); 
  //  delayMicroseconds(2); 

  //  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(10); 
   
  //  digitalWrite(trigPin, LOW);
  //  duration = pulseIn(echoPin, HIGH);
   
  //  //Calculate the distance (in cm) based on the speed of sound.
  //  distance = duration/58.2;
   
  //  if (distance >= maximumRange || distance <= minimumRange){
  //    /* Send a negative number to computer and Turn LED ON 
  //    to indicate "out of range" */
  //    lcd.clear();
  //    lcd.write("Out of range");
  //  }
  //  else {
  //    /* Send the distance to the computer using Serial protocol, and
  //    turn LED OFF to indicate successful reading. */
  //    Serial.println(distance);
  //    lcd.clear();
  //    lcd.print(String(distance) + " cm");
  //  }
  // lcd.setCursor(0, 1);
  // lcd.print(String(count) + " under 10cm.");
}