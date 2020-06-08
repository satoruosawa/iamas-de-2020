#include <M5Stack.h>

int second = 0;

void setup() { M5.begin(); }

void loop() {
  M5.update();  // ボタンかスピーカーを使うときは、この行を追加する。
  if (second < millis() / 1000) {
    M5.Speaker.tone(3520, 10);
    second++;
  }
  delay(10);
}
