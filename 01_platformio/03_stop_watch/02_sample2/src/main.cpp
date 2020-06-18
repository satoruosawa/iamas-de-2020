#include <M5Stack.h>

bool is_playing = false;
float accumulate_sec = 0;
float last_measure_sec = 0;
float measure_sec = 0;
float start_sec = 0;

int center_x = 160;
int center_y = 120;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
}

void buttonManagement() {
  if (is_playing) {
    if (M5.BtnC.wasPressed()) {
      is_playing = false;
      M5.Speaker.tone(3520, 20);
    } else {
      measure_sec = millis() / 1000.0 - start_sec + accumulate_sec;
    }
  } else {
    if (M5.BtnA.wasPressed()) {
      measure_sec = 0;
      accumulate_sec = 0;
      M5.Lcd.clear();
      M5.Speaker.tone(3520, 20);
    }
    if (M5.BtnC.wasPressed()) {
      start_sec = millis() / 1000.0;
      accumulate_sec = measure_sec;
      is_playing = true;
      M5.Speaker.tone(3520, 20);
    }
  }
}

void drawSecond() {
  float measure_min = measure_sec / 60;
  float last_measure_min = last_measure_sec / 60;
  if (fmod(measure_min, 1) < fmod(last_measure_min, 1)) {
    M5.lcd.fillEllipse(center_x, center_y, 100, 100, BLACK);
  }
  float div = 100;
  float quantum = (floor)(fmod(measure_min, 1) * div) / div;
  float quantum_angle = quantum * 2 * M_PI - M_PI / 2.0;
  int x0 = 90 * cos(quantum_angle) + center_x;
  int x1 = 95 * cos(quantum_angle) + center_x;
  int y0 = 90 * sin(quantum_angle) + center_y;
  int y1 = 95 * sin(quantum_angle) + center_y;
  M5.Lcd.drawLine(x0, y0, x1, y1, WHITE);
}

void drawBelowSecond() {
  if (fmod(measure_sec, 1) < fmod(last_measure_sec, 1)) {
    M5.lcd.fillEllipse(center_x, center_y, 86, 86, BLACK);
  }
  float div = 50;
  float quantum = (floor)(fmod(measure_sec, 1) * div) / div;
  float quantum_angle = quantum * 2 * M_PI - M_PI / 2.0;
  int x0 = 80 * cos(quantum_angle) + center_x;
  int x1 = 85 * cos(quantum_angle) + center_x;
  int y0 = 80 * sin(quantum_angle) + center_y;
  int y1 = 85 * sin(quantum_angle) + center_y;
  M5.Lcd.drawLine(x0, y0, x1, y1, WHITE);
}

void drawTimeCenter() {
  int font_width = 18;
  int digit = 0;
  if (measure_sec > 1) {
    digit = (int)log10(measure_sec);
  }
  M5.Lcd.setCursor(center_x - (digit + 4) * font_width / 2, 105);
  M5.Lcd.print(measure_sec);
}

void loop() {
  M5.update();
  buttonManagement();
  drawSecond();
  drawBelowSecond();
  drawTimeCenter();
  last_measure_sec = measure_sec;
  delay(2);
}
