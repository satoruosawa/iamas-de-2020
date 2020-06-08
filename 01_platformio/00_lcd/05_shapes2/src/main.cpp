#include <M5Stack.h>

int x = 0;
int y = 0;

void setup() { M5.begin(); }

void loop() {
  M5.Lcd.fillRect(x, y, 18, 18, WHITE);

  x = x + 20;
  if (x >= 320) {
    x = 0;
    y = y + 20;
  }

  delay(100);
}
