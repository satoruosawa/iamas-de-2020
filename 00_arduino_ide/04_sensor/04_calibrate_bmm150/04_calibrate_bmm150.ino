#include <M5Stack.h>
// WireライブラリはM5Stackライブラリの中で既にincludeされているので、
// ここでincludeする必要はないです。
// #include <Wire.h>  // 磁気センサーライブラリはWireライブラリも必要

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
  M5.update();        // ボタンを使うので必要
  m5Bmm150.update();  // 磁気センサーデータの更新

  M5.Lcd.setCursor(0, 0);

  float mag_x;  // X軸方向の磁気データを受け取るための変数
  float mag_y;  // Y軸方向の磁気データを受け取るための変数
  float mag_z;  // Z軸方向の磁気データを受け取るための変数
  m5Bmm150.getCalibratedData(&mag_x, &mag_y, &mag_z);  // 磁気データを取得
  M5.Lcd.printf("Calibrated data:\n  X: %5.2f\n  Y: %5.2f\n  Z: %5.2f\n", mag_x,
                mag_y, mag_z);

  float dir = m5Bmm150.getHeadDirection();  //デバイスの向きを取得
  M5.Lcd.printf("Direction: %7.2f[deg]", dir);

  M5.Lcd.setCursor(0, 180);
  M5.Lcd.print("Press Button A to start \ncalibration.");

  if (M5.BtnA.wasPressed()) {
    // キャリブレーションモード
    M5.Lcd.setTextSize(2);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 110);
    M5.Lcd.print("Flip + rotate M5Stack GREY");

    m5Bmm150.calibrate(20000);  // 20秒間キャリブレーション

    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 110);
    M5.Lcd.print("Done calibration.");
    delay(1000);
    M5.Lcd.clear(BLACK);
  }
  delay(100);
}