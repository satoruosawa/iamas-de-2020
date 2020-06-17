#include <M5Stack.h>

int rect_width = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  M5.Lcd.fillRect(rect_width - 1, 0, 1, 240, WHITE);
  M5.Lcd.fillRect(rect_width, 0, 1, 240, BLACK);

  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rect_width += 1;
  } else {
    rect_width -= 1;
  }

  rect_width = constrain(rect_width, 0, 320);
  delay(4);
}
