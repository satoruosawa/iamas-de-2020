#define M5STACK_MPU6886  // #include <M5Stack.h> の前にこの行を追加

#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサかジャイロセンサを使うときはこの行を追加
  M5.IMU.Init();  // 加速度センサかジャイロセンサを使うときはこの行を追加

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
}

void loop() {
  float acc_x = 0.0;
  float acc_y = 0.0;
  float acc_z = 0.0;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Acceleration Sensor");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("X: %5.2f G\nY: %5.2f G\nZ: %5.2f G", acc_x, acc_y, acc_z);
  delay(1);
}