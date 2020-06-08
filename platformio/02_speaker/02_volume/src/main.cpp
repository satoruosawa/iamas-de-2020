#include <M5Stack.h>

int volume = 1;
void setup() {
  M5.begin();
  M5.Speaker.setVolume(volume);
}

void loop() {
  M5.update();  // ボタンかスピーカーを使うときは、この行を追加する。
  if (M5.BtnA.wasPressed()) {
    volume--;
    M5.Speaker.setVolume(volume);
  }
  if (M5.BtnB.wasPressed()) {
    M5.Speaker.tone(3520, 20);
  }
  if (M5.BtnC.wasPressed()) {
    volume++;
    M5.Speaker.setVolume(volume);
  }

  volume = constrain(volume, 0, 10);

  M5.Lcd.setCursor(100, 100);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Volume = ");
  M5.Lcd.print(volume);
  M5.Lcd.print(" ");
  delay(10);
}
