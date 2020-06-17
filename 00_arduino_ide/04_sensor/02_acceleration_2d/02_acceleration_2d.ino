#define M5STACK_MPU6886  // この行は #include <M5Stack.h> より先に記述する

#include <M5Stack.h>

float accX = 0.0;
float accY = 0.0;
float accZ = 0.0;

int prevX = 0;
int prevY = 0;

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

  M5.Lcd.drawLine(0, 120, 320, 120, TFT_DARKGREY);
  M5.Lcd.drawLine(160, 20, 160, 240, TFT_DARKGREY);
  M5.Lcd.drawCircle(160, 120, 80, TFT_DARKGREY);
  int x = map(accX * 100, -1 * 100, 1 * 100, 240, 80);
  int y = map(accY * 100, -1 * 100, 1 * 100, 40, 200);
  M5.Lcd.fillCircle(prevX, prevY, 10, BLACK);
  M5.Lcd.fillCircle(x, y, 10, WHITE);
  prevX = x;
  prevY = y;

  delay(1);
}