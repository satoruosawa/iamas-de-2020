#include <M5Stack.h>

int rect_height = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  M5.Lcd.fillRect(0, 240 - rect_height + 1, 320, 1, WHITE);
  M5.Lcd.fillRect(0, 240 - rect_height, 320, 1, BLACK);

  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rect_height += 1;
  } else {
    rect_height -= 1;
  }

  rect_height = constrain(rect_height, 0, 240);
  delay(2);
}