#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.fillCircle(80, 120, 50, WHITE);      // 円(塗りつぶし)を描画
  M5.Lcd.fillRect(190, 70, 100, 100, WHITE);  // 四角(塗りつぶし)を描画
}

void loop() {}
