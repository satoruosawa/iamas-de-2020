#define M5STACK_MPU6886

#include <M5Stack.h>

float integral_gyro_x = 0.0;
float integral_gyro_y = 0.0;
float integral_gyro_z = 0.0;
float prev_loop_sec = 0.0;

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

  // 角速度の積分
  float sec = micros() / 1000000.0;
  float diff_sec = sec - prev_loop_sec;
  prev_loop_sec = sec;
  integral_gyro_x += diff_sec * gyro_x;
  integral_gyro_y += diff_sec * gyro_y;
  integral_gyro_z += diff_sec * gyro_z;

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Gyro sensor integration");
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.printf("X:%4.0f[deg]\nY:%4.0f[deg]\nZ:%4.0f[deg]", integral_gyro_x,
                integral_gyro_y, integral_gyro_z);
}