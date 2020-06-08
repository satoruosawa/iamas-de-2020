#include <M5Stack.h>

int number = 0;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(4);
}

void loop() {
  M5.Lcd.setCursor(150, 100);
  M5.Lcd.println(number);
  number++;
  delay(1000);
}
