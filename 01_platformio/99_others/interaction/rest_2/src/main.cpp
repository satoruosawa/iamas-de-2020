#define M5STACK_MPU6886  // #include <M5Stack.h> の前にこの行を追加

#include <M5Stack.h>

float prev_acc_x, prev_acc_y, prev_acc_z;

unsigned long wakeup_start;

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサかジャイロセンサを使うときはこの行を追加
  M5.IMU.Init();  // 加速度センサかジャイロセンサを使うときはこの行を追加

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  wakeup_start = millis();
}

void loop() {
  float acc_x, acc_y, acc_z;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  float diff_x = acc_x - prev_acc_x;
  float diff_y = acc_y - prev_acc_y;
  float diff_z = acc_z - prev_acc_z;
  prev_acc_x = acc_x;
  prev_acc_y = acc_y;
  prev_acc_z = acc_z;

  float margin = 0.1;
  if (abs(diff_x) < margin && abs(diff_y) < margin && abs(diff_z) < margin) {
  } else {
    wakeup_start = millis();
  }
  if (millis() - wakeup_start > 5000) {
    M5.Lcd.clear(BLACK);
  } else {
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Acceleration Sensor");
    M5.Lcd.setCursor(0, 60);
    // printf関数によって、通常のC言語フォーマットに沿った書式指定ができる。
    // %5.2f　は、右詰め, 5マス分の幅, 小数点以下を2桁に揃える。
    M5.Lcd.printf("X: %5.2f G\nY: %5.2f G\nZ: %5.2f G", acc_x, acc_y, acc_z);
  }

  delay(1);
}