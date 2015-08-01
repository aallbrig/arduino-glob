#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
  Serial.begin(9600);
  // Define LCD Display
  lcd.begin(16, 2);
  // any one-time tests
  /*testLcdDisplay();*/
}

void loop(){
  if (Serial.available()) {
    lcd.write(Serial.read());
  }
}
