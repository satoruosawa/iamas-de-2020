#define M5STACK_MPU6886  // #include <M5Stack.h> の前にこの行を追加

#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサかジャイロセンサを使うときはこの行を追加
  M5.IMU.Init();  // 加速度センサかジャイロセンサを使うときはこの行を追加

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
}

void loop() {
  float acc_x;  // X軸方向の加速度データを受け取るための変数
  float acc_y;  // Y軸方向の加速度データを受け取るための変数
  float acc_z;  // Z軸方向の加速度データを受け取るための変数
  // getAccelData関数はポインタ渡しでデータを取得する。
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Acceleration Sensor");
  M5.Lcd.setCursor(0, 40);
  // printf関数によって、通常のC言語フォーマットに沿った書式指定ができる。
  // %5.2f　は、右詰め, 5マス分の幅, 小数点以下を2桁に揃える。
  M5.Lcd.printf("X: %5.2f G\nY: %5.2f G\nZ: %5.2f G", acc_x, acc_y, acc_z);

  delay(1);
}