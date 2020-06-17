#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>
#include <MadgwickAHRS.h>
#include <Wire.h>

#include "m5bmm150.h"

M5Bmm150 m5Bmm150;
Madgwick filter;

float acc_x = 0.0;
float acc_y = 0.0;
float acc_z = 0.0;

float gyro_x = 0.0F;
float gyro_y = 0.0F;
float gyro_z = 0.0F;

float mag_x = 0.0F;
float mag_y = 0.0F;
float mag_z = 0.0F;

unsigned long loop_interval, prev_update;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  int freq = 10;  // micro sec
  loop_interval = 1000000 / freq;
  filter.begin(freq);
  Wire.begin(21, 22, 400000);
  if (m5Bmm150.initialize() != BMM150_OK) {
    M5.Lcd.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5Bmm150.loadOffset();
  delay(100);

  M5.lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);
  prev_update = micros();
}

void loop() {
  if (micros() - prev_update < loop_interval) return;
  prev_update = micros();
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  m5Bmm150.update();
  m5Bmm150.getMagData(&mag_x, &mag_y, &mag_z);
  // filter.updateIMU(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);
  filter.update(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z, mag_x, mag_y,
                mag_z);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Gyro:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", gyro_x, gyro_y,
                gyro_z);
  M5.Lcd.printf("Mag:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", mag_x, mag_y,
                mag_z);
  M5.Lcd.printf("Rotaion:\n  Pitch: %7.2f\n  Roll: %7.2f\n  Yaw: %7.2f\n",
                filter.getPitch(), filter.getRoll(), filter.getYaw());
}
