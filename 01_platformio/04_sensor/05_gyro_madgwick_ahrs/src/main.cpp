#define M5STACK_MPU6886  // この行は #include <M5Stack.h> より先に記述する

#include <M5Stack.h>
#include <MadgwickAHRS.h>

Madgwick filter;

float accX = 0.0;
float accY = 0.0;
float accZ = 0.0;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

unsigned long loop_interval, prev_update;

void setup() {
  M5.begin();
  M5.Power.begin();  // 加速度センサを使うときはこの行を追加する。
  M5.IMU.Init();  // 加速度センサを使うときはこの行を追加する。
  int freq = 10;  // micro sec
  loop_interval = 1000000 / freq;
  filter.begin(freq);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  prev_update = micros();
}

void loop() {
  if (micros() - prev_update < loop_interval) return;
  prev_update = micros();
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  filter.updateIMU(gyroX, gyroY, gyroZ, accX, accY, accZ);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Gyro Sensor");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Pitch:%7.2f[deg]\nRoll:%7.2f[deg]\nYaw:%7.2f[deg]",
                filter.getPitch(), filter.getRoll(), filter.getYaw());
}