#include <M5Stack.h>

int number = 0;  // numberという名前の変数を宣言

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(4);
}

void loop() {
  M5.Lcd.setCursor(150, 100);
  M5.Lcd.println(number);
  number++;     // numberに1追加
  delay(1000);  // 1000ミリ秒 = 1秒間 待つ
}
