#define M5STACK_MPU6886

#include <M5Stack.h>
#include <MadgwickAHRS.h>

Madgwick filter;

unsigned long loop_interval_microsec, prev_loop;
int sampling_freq = 25;  // Hz

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  filter.begin(sampling_freq);

  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextSize(2);
  loop_interval_microsec = 1000000 / sampling_freq;
  prev_loop = micros();
}

void loop() {
  unsigned long now = micros();
  if (now < prev_loop + loop_interval_microsec) return;

  float acc_x = 0.0;
  float acc_y = 0.0;
  float acc_z = 0.0;
  float gyro_x = 0.0;
  float gyro_y = 0.0;
  float gyro_z = 0.0;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  filter.updateIMU(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);

  // LCD 表示
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf("Rotation");
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.printf("Pitch:%7.2f[deg]\n Roll:%7.2f[deg]\n  Yaw:%7.2f[deg]",
                filter.getPitch(), filter.getRoll(), filter.getYaw());
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_loop));

  prev_loop = now;
}