#define M5STACK_MPU6886

#include <M5Stack.h>

// M5Stackのライブラリー内のAHRSは更新周波数25Hzに固定されている。
// 1000000[micro sec] / 25[Hz]
unsigned long interval = 1000000 / 25;
unsigned long prev_update = 0;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  prev_update = micros();
}

void loop() {
  // 更新周波数を25Hzに制御するためのアルゴリズム。
  unsigned long now = micros();
  if (now < prev_update + interval) return;

  float pitch = 0.0;
  float roll = 0.0;
  float yaw = 0.0;
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Rotation");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf(" Roll:%7.2f[deg]\nPitch:%7.2f[deg]\n  Yaw:%7.2f[deg]", roll,
                pitch, yaw);

  // 実際の更新周波数 = 1 / 期間[秒]
  // 実際の更新周波数が25Hz以下になると、正確に計算できない
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_update));

  prev_update = now;  // 更新周波数を25Hzに制御するためのアルゴリズム。
}