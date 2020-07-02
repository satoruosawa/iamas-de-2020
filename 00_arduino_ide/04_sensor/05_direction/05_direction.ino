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
  M5.Lcd.setTextSize(3);
}

void loop() {
  m5Bmm150.update();  // 磁気センサーデータの更新

  float dir = m5Bmm150.getHeadDirection();  //デバイスの向きを取得

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Direction:\n  %7.2f[deg]", dir);

  delay(100);
}