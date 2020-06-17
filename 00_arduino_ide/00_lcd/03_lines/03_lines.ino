#include <M5Stack.h>

void setup() {
  M5.begin();

  // iの値が0から4(5未満)まで1つずつ変化
  // 0 -> 1 -> 2 -> 3 -> 4 end.
  for (int i = 0; i < 5; i++) {
    int y = (i + 1) * 40;
    M5.Lcd.drawLine(10, y, 310, y, WHITE);
  }
  for (int i = 0; i < 7; i++) {
    int x = (i + 1) * 40;
    M5.Lcd.drawLine(x, 10, x, 230, WHITE);
  }
}

void loop() {}
