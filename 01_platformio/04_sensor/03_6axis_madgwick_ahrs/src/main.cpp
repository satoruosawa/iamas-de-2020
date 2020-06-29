#define M5STACK_MPU6886

#include <M5Stack.h>
#include <MadgwickAHRS.h>  // Madgwickフィルターのライブラリを使うための宣言

Madgwick filter;  // Madgwickフィルターのライブラリを使うための定義

const int update_freq = 20;  // 更新周波数[Hz]
unsigned long interval;      // アップデートの間隔[マイクロ秒]
unsigned long prev_update;  // 前のアップデートの時間[マイクロ秒]

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  filter.begin(update_freq);  // フィルターの初期設定

  interval = 1000000 / update_freq;  // = 40000マイクロ秒 = 0.04秒
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
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  // フィルターのアップデートをする。加速度センサとジャイロセンサの値を渡すことで、
  // 裏側で姿勢データを計算している。
  filter.updateIMU(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Rotation");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Pitch:%7.2f[deg]\n Roll:%7.2f[deg]\n  Yaw:%7.2f[deg]",
                filter.getPitch(), filter.getRoll(), filter.getYaw());

  // 実際の更新周波数 = 1 / 期間[秒]
  // 実際の更新周波数が設定値(20Hz)以下になると、正確に計算できない
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_update));

  prev_update = now;  // 更新周波数を20Hzに制御するためのアルゴリズム。
}