#include <M5Stack.h>  // M5Stackのライブラリを利用するための宣言

void setup() {
  // setup関数は、起動時に一度だけ呼ばれる関数

  M5.begin();  // M5Stackオブジェクトの初期化

  M5.Lcd.setTextSize(2);           // テキストのサイズを指定
  M5.Lcd.setCursor(0, 10);         // カーソルの位置を指定
  M5.Lcd.println("Hello world.");  // 文字列を表示
}

void loop() {
  // loop関数は、setup関数のあとに繰り返し呼ばれる関数
}