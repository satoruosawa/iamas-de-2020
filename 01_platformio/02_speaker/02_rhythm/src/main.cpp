#include <M5Stack.h>

unsigned long prev_update = 0;
float tempo = 60.0;  // BPM

void setup() { M5.begin(); }

void loop() {
  M5.update();
  if (millis() < prev_update + 60 * 1000 / tempo) return;
  prev_update = millis();
  M5.Speaker.tone(3520, 20);
}

// void loop() {
//   M5.update();
//   M5.Speaker.tone(3520, 20);
//   delay(60 * 1000 / tempo);
// }