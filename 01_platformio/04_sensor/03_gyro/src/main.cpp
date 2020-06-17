#define M5STACK_MPU6886  // この行は #include <M5Stack.h> より先に記述する

#include <M5Stack.h>

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサを使うときはこの行を追加する。
  M5.IMU.Init();  // 加速度センサを使うときはこの行を追加する。

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
}

// the loop routine runs over and over again forever
void loop() {
  // put your main code here, to run repeatedly:
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Gyro Sensor");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("X:%4.0f[deg/s]\nY:%4.0f[deg/s]\nZ:%4.0f[deg/s]", gyroX, gyroY,
                gyroZ);
  delay(1);
}