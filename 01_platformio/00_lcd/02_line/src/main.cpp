#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.drawLine(10, 10, 200, 200, WHITE);  // 座標を指定して線を描画
}

void loop() {}
