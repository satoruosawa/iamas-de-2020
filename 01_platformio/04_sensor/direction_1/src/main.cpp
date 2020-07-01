#include <M5Stack.h>
#include <Wire.h>  // 磁気センサーライブラリはWireライブラリも必要

#include "./m5bmm150.h"  // 磁気センサーライブラリを使うための宣言

M5Bmm150 m5Bmm150;  // 磁気センサーライブラリを使うための定義

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
  int radius = 50;

  M5.Lcd.fillCircle(center_x, center_y, radius + 1, BLACK);
  int x = radius * cos((-dir - 90.0) * M_PI / 180.0) + center_x;
  int y = radius * sin((-dir - 90.0) * M_PI / 180.0) + center_y;
  M5.Lcd.drawLine(center_x, center_y, x, y, WHITE);

  delay(100);
}