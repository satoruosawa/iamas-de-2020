#include <M5Stack.h>

void setup() { M5.begin(); }

void loop() {
  M5.update();  // ボタンかスピーカーを使うときは、この行を追加
  if (M5.BtnA.wasPressed()) {
    M5.Speaker.tone(3135, 20);  // 3135Hzの音を20ミリ秒再生
  }
  if (M5.BtnB.wasPressed()) {
    M5.Speaker.tone(3520, 20);  // 3520Hzの音を20ミリ秒再生
  }
  if (M5.BtnC.wasPressed()) {
    M5.Speaker.tone(3951, 20);  // 3951Hzの音を20ミリ秒再生
  }
}
