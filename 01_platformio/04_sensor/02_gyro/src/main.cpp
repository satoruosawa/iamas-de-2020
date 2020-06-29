#define M5STACK_MPU6886

#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
}

void loop() {
  float gyro_x;  // X軸方向のジャイロデータを受け取るための変数
  float gyro_y;  // Y軸方向のジャイロデータを受け取るための変数
  float gyro_z;  // Z軸方向のジャイロデータを受け取るための変数

  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);  // ジャイロデータを取得

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Gyro Sensor");
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.printf("X:%4.0f[deg/s]\nY:%4.0f[deg/s]\nZ:%4.0f[deg/s]", gyro_x,
                gyro_y, gyro_z);

  delay(1);
}