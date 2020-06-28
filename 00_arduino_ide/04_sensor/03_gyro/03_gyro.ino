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
  float gyro_x = 0.0;
  float gyro_y = 0.0;
  float gyro_z = 0.0;
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Gyro Sensor");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("X:%4.0f[deg/s]\nY:%4.0f[deg/s]\nZ:%4.0f[deg/s]", gyro_x,
                gyro_y, gyro_z);
  delay(1);
}