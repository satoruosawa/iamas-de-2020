#define M5STACK_MPU6886

#include <M5Stack.h>

int x = 0;

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
  // 上段のテキスト描画
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.println("Accelaration Sensor.");
  M5.Lcd.setTextColor(RED, BLACK);
  M5.Lcd.printf("X:%5.2fG ", acc_x);
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.printf("Y:%5.2fG ", acc_y);
  M5.Lcd.setTextColor(BLUE, BLACK);
  M5.Lcd.printf("Z:%5.2fG", acc_z);

  // グラフ描画
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.drawLine(0, 100, 320, 100, WHITE);
  M5.Lcd.drawLine(0, 150, 320, 150, WHITE);
  M5.Lcd.drawLine(0, 200, 320, 200, WHITE);
  M5.Lcd.setCursor(0, 80);
  M5.Lcd.print("+1");
  M5.Lcd.setCursor(0, 205);
  M5.Lcd.print("-1");
  M5.Lcd.drawPixel(x, 150 - (int)(acc_x * 50), RED);
  M5.Lcd.drawPixel(x, 150 - (int)(acc_y * 50), GREEN);
  M5.Lcd.drawPixel(x, 150 - (int)(acc_z * 50), BLUE);

  x++;
  // グラフが一番右まで行ったら画面をリセット
  if (x > 320) {
    M5.Lcd.clear(BLACK);
    x = 0;
  }
  delay(1);
}