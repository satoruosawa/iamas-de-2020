#define M5STACK_MPU6886

#include <M5Stack.h>

int prev_x = 0;
int prev_y = 0;

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

  M5.Lcd.drawLine(0, 120, 320, 120, TFT_DARKGREY);
  M5.Lcd.drawLine(160, 20, 160, 240, TFT_DARKGREY);
  M5.Lcd.drawCircle(160, 120, 80, TFT_DARKGREY);
  int x = map(acc_x * 100, -1 * 100, 1 * 100, 240, 80);
  int y = map(acc_y * 100, -1 * 100, 1 * 100, 40, 200);
  M5.Lcd.fillCircle(prev_x, prev_y, 10, BLACK);
  M5.Lcd.fillCircle(x, y, 10, WHITE);
  prev_x = x;
  prev_y = y;

  delay(1);
}