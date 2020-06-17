#include <M5Stack.h>

int rect_width = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(0, 0, rect_width, 240, WHITE);
  // M5.Lcd.fillRect(rect_width, 0, 320 - rect_width, 240, BLACK);

  // M5.BtnA.wasPressed() はボタンを押したときに1度しかtrueにならないので、
  // pressingというフラグを立てる。
  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rect_width += 10;
  } else {
    rect_width -= 10;
  }

  rect_width = constrain(rect_width, 0, 320);
  delay(10);
}
