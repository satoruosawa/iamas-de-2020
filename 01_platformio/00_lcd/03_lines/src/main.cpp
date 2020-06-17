#include <M5Stack.h>

void setup() {
  M5.begin();

  // iの値が0から4(5未満)まで1つずつ変化
  // 0 -> 1 -> 2 -> 3 -> 4
  for (int i = 0; i < 5; i++) {
    // 横の線を5本描画
    int y = (i + 1) * 40;
    M5.Lcd.drawLine(10, y, 310, y, WHITE);
  }
  for (int i = 0; i < 7; i++) {
    // 縦の線を7本描画
    int x = (i + 1) * 40;
    M5.Lcd.drawLine(x, 10, x, 230, WHITE);
  }
}

void loop() {}
