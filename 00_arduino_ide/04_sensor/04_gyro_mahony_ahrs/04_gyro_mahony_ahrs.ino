#define M5STACK_MPU6886  // この行は #include <M5Stack.h> より先に記述する

#include <M5Stack.h>

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサを使うときはこの行を追加する。
  M5.IMU.Init();  // 加速度センサを使うときはこの行を追加する。

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Gyro Sensor");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Pitch:%7.2f[deg]\nRoll:%7.2f[deg]\nYaw:%7.2f[deg]", pitch,
                roll, yaw);
  delay(1);
}