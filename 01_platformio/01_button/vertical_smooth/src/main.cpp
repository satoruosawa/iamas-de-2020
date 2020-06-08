#include <M5Stack.h>

int rectHeight = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  M5.Lcd.fillRect(0, 240 - rectHeight + 1, 320, 1, WHITE);
  M5.Lcd.fillRect(0, 240 - rectHeight, 320, 1, BLACK);

  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rectHeight += 1;
  } else {
    rectHeight -= 1;
  }

  rectHeight = constrain(rectHeight, 0, 240);
  delay(2);
}