#include <M5Stack.h>

int rectWidth = 0;
bool pressing = false;

void setup() { M5.begin(); }

void loop() {
  M5.update();
  M5.Lcd.clear(BLACK);
  M5.Lcd.fillRect(0, 0, rectWidth, 240, WHITE);
  // M5.Lcd.fillRect(rectWidth, 0, 320 - rectWidth, 240, BLACK);

  // M5.BtnA.wasPressed() はボタンを押したときに1度しか呼ばれないので、
  // pressingというフラグを立てる。
  if (M5.BtnA.wasPressed()) {
    pressing = true;
  }
  if (M5.BtnA.wasReleased()) {
    pressing = false;
  }

  if (pressing) {
    rectWidth += 10;
  } else {
    rectWidth -= 10;
  }

  rectWidth = constrain(rectWidth, 0, 320);
  delay(10);
}
