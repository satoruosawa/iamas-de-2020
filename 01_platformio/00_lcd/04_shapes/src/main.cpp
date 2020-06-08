#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.fillEllipse(80, 120, 50, 50, WHITE);
  M5.Lcd.fillRect(190, 70, 100, 100, WHITE);
}

void loop() {}
