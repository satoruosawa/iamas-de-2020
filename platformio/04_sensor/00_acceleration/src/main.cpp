#define M5STACK_MPU6886  // この行は #include <M5Stack.h> より先に記述する

#include <M5Stack.h>

float accX = 0.0;
float accY = 0.0;
float accZ = 0.0;

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサを使うときはこの行を追加する。
  M5.IMU.Init();  // 加速度センサを使うときはこの行を追加する。

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("%5.2fG %5.2fG %5.2fG", accX, accY, accZ);
  delay(1);
}