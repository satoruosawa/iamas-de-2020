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

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("X:%5.2fG Y:%5.2fG Z:%5.2fG", accX, accY, accZ);

  int x = map(accX * 100, -200, 200, 280, 40);
  int y = map(accY * 100, -200, 200, 0, 240);
  M5.Lcd.drawPixel(x, y, WHITE);

  delay(1);
}