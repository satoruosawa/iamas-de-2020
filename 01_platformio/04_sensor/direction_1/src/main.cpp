#include <M5Stack.h>
#include <Wire.h>  // 磁気センサーライブラリはWireライブラリも必要

#include "./m5bmm150.h"  // 磁気センサーライブラリを使うための宣言

M5Bmm150 m5Bmm150;  // 磁気センサーライブラリを使うための定義

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
}

uint16_t getColor(uint8_t grey) { return getColor(grey, grey, grey); }

void setup() {
  M5.begin();
  Wire.begin(21, 22, 400000);  // Wireライブラリの初期設定

  if (m5Bmm150.initialize() != BMM150_OK) {  // 磁気センサーライブラリの初期設定
    M5.Lcd.println("BMM150 initialization failed.");
    while (1)
      ;
  }

  m5Bmm150.loadOffset();  // キャリブレーションデータをロード
  M5.Lcd.setTextSize(2);
}

void loop() {
  m5Bmm150.update();  // 磁気センサーデータの更新

  float dir = m5Bmm150.getHeadDirection();  //デバイスの向きを取得

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Direction: %7.2f[deg]", dir);
  int center_x = 160;
  int center_y = 120;
  int radius = 70;

  M5.Lcd.drawCircle(center_x, center_y, radius + 15, getColor(50));
  for (int i = 0; i < 24; i++) {
    float angle = i / 24.0 * 2 * M_PI;
    int in_r = radius + 10;
    int out_r = radius + 15;
    uint32_t c = getColor(50);
    if (i % 6 == 0) {
      in_r = radius + 5;
      out_r = radius + 15;
    }
    if (i == 18) {
      c = RED;
    }
    int x0 = in_r * cos(angle) + center_x;
    int y0 = in_r * sin(angle) + center_y;
    int x1 = out_r * cos(angle) + center_x;
    int y1 = out_r * sin(angle) + center_y;
    M5.Lcd.drawLine(x0, y0, x1, y1, c);
  }
  M5.Lcd.fillCircle(center_x, center_y, radius + 2, BLACK);
  int x = radius * cos((-dir - 90.0) * M_PI / 180.0) + center_x;
  int y = radius * sin((-dir - 90.0) * M_PI / 180.0) + center_y;
  M5.Lcd.drawLine(center_x, center_y, x, y, WHITE);

  delay(10);
}