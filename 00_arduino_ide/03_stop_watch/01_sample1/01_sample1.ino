#include <M5Stack.h>

float start_sec = 0;
float measure_sec = 0;
float accumulate_sec = 0;
bool is_playing = false;
int rect_count = 0;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
}

void loop() {
  M5.update();

  if (is_playing) {
    if (M5.BtnC.wasPressed()) {
      is_playing = false;
    } else {
      measure_sec = millis() / 1000.0 - start_sec + accumulate_sec;
    }
  } else {
    if (M5.BtnA.wasPressed()) {
      measure_sec = 0;
      accumulate_sec = 0;
      M5.Lcd.clear();
    }
    if (M5.BtnC.wasPressed()) {
      start_sec = millis() / 1000.0;
      accumulate_sec = measure_sec;
      is_playing = true;
    }
  }
  int x = fmod(measure_sec, 10) / 10 * 320;  // fmodは10で割った余り
  int y = floor(measure_sec / 10);           // floorは切り捨て

  M5.Lcd.drawRect(x, y * 20 + 40, -20, 20, WHITE);

  M5.Lcd.setCursor(10, 10);
  M5.Lcd.print(measure_sec);
  delay(10);
}
