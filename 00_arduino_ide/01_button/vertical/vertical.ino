#include <M5Stack.h>

int rectHeight = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  // M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(0, 240 - rectHeight, 320, rectHeight, WHITE);
  M5.Lcd.fillRect(0, 0, 320, 240 - rectHeight, BLACK);

  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rectHeight += 10;
  } else {
    rectHeight -= 10;
  }

  rectHeight = constrain(rectHeight, 0, 240);
  delay(10);
}
