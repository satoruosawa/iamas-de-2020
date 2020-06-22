#define M5STACK_MPU6886

#include <M5Stack.h>

unsigned long loop_interval_micros =
    1000000 / 25;  // = 1000000[micro sec] / 25[Hz]
unsigned long prev_loop = 0UL;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  prev_loop = micros();
}

void loop() {
  unsigned long now = micros();
  if (now < prev_loop + loop_interval_micros) return;

  float pitch = 0.0;
  float roll = 0.0;
  float yaw = 0.0;
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Rotation");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Pitch:%7.2f[deg]\nRoll:%7.2f[deg]\nYaw:%7.2f[deg]", pitch,
                roll, yaw);

  // loop周波数が25Hz以下になると、計算精度が落ちる
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_loop));
  prev_loop = now;
}