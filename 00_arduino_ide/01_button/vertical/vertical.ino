#include <M5Stack.h>

int rect_height = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  // M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(0, 240 - rect_height, 320, rect_height, WHITE);
  M5.Lcd.fillRect(0, 0, 320, 240 - rect_height, BLACK);

  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rect_height += 10;
  } else {
    rect_height -= 10;
  }

  rect_height = constrain(rect_height, 0, 240);
  delay(10);
}
