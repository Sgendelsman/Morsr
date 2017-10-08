#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
  Wire.begin(LCD_ADDRESS);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.blinkLED();
  lcd.print("Hello, World!");
  
}

void loop() {
  // put your main code here, to run repeatedly
  
}
