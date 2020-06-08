#include <M5Stack.h>

int rectWidth = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  M5.Lcd.fillRect(rectWidth - 1, 0, 1, 240, WHITE);
  M5.Lcd.fillRect(rectWidth, 0, 1, 240, BLACK);

  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rectWidth += 1;
  } else {
    rectWidth -= 1;
  }

  rectWidth = constrain(rectWidth, 0, 320);
  delay(4);
}
