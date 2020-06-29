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
  float acc_x = 0.0;
  float acc_y = 0.0;
  float acc_z = 0.0;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("X:%5.2fG Y:%5.2fG Z:%5.2fG", acc_x, acc_y, acc_z);

  int x = map(acc_x * 100, -200, 200, 280, 40);
  int y = map(acc_y * 100, -200, 200, 0, 240);
  M5.Lcd.drawPixel(x, y, WHITE);

  delay(1);
}