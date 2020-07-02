#define M5STACK_MPU6886

#include <M5Stack.h>
#include <MadgwickAHRS.h>

#include "./m5bmm150.h"

M5Bmm150 m5Bmm150;
Madgwick filter;

const int update_freq = 20;
unsigned long interval;
unsigned long prev_update;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  filter.begin(update_freq);
  Wire.begin(21, 22, 400000);

  if (m5Bmm150.initialize() != BMM150_OK) {
    M5.Lcd.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5Bmm150.loadOffset();

  interval = 1000000 / update_freq;
  prev_update = micros();
  M5.Lcd.setTextSize(2);
}

void loop() {
  // 更新周波数を制御するためのアルゴリズム。
  unsigned long now = micros();
  if (now < prev_update + interval) return;

  float acc_x;
  float acc_y;
  float acc_z;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float mag_x;
  float mag_y;
  float mag_z;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  // フィルターのアップデートをする。加速度センサとジャイロセンサの値を渡すことで、
  // 裏側で姿勢データを計算している。
  m5Bmm150.update();
  m5Bmm150.getCalibratedData(&mag_x, &mag_y, &mag_z);
  filter.update(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z, mag_x, -mag_y,
                mag_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Rotation");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("   Roll:%7.2f[deg]\n  Pitch:%7.2f[deg]\n    Yaw:%7.2f[deg]",
                filter.getRoll(), filter.getPitch(), filter.getYaw());

  // 実際の更新周波数 = 1 / 期間[秒]
  // 実際の更新周波数が設定値(20Hz)以下になると、正確に計算できない
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_update));

  prev_update = now;  // 更新周波数を20Hzに制御するためのアルゴリズム。
}