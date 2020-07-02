#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>
#include <MadgwickAHRS.h>

#include "./m5bmm150.h"
#include "./wifi-info.h"

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

M5Bmm150 m5Bmm150;
Madgwick filter;

unsigned long interval, prev_update;
int update_freq = 20;  // Hz

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  interval = 1000000 / update_freq;
  filter.begin(update_freq);

  M5.lcd.setTextSize(1);
  Wire.begin(21, 22, 400000);
  if (m5Bmm150.initialize() != BMM150_OK) {
    M5.Lcd.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5Bmm150.loadOffset();
  delay(100);

  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  delay(100);

  M5.Lcd.clear(BLACK);
  prev_update = micros();
}

void loop() {
  unsigned long now = micros();
  if (now < prev_update + interval) return;

  // センサーデータの更新
  float acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z, mag_x, mag_y, mag_z;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);
  M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
  m5Bmm150.update();
  m5Bmm150.getCalibratedData(&mag_x, &mag_y, &mag_z);
  filter.update(gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z, mag_x, -mag_y,
                mag_z);
  float dir = m5Bmm150.getHeadDirection();

  // OSC送信
  OscWiFi.update();
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/acceleration", acc_x, acc_y,
               acc_z);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/gyro", gyro_x, gyro_y,
               gyro_z);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/magnetic_field", mag_x, mag_y,
               mag_z);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/direction", dir);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/roll", filter.getRoll());
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/pitch", filter.getPitch());
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/yaw", filter.getYaw());

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.print(TARGEET_IP.c_str());
  M5.Lcd.print(":");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.println();
  M5.Lcd.printf("Acceleration:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", acc_x,
                acc_y, acc_z);
  M5.Lcd.printf("Gyro:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", gyro_x, gyro_y,
                gyro_z);
  M5.Lcd.printf("Magnetic Field:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", mag_x,
                mag_y, mag_z);
  M5.Lcd.printf("direction: %7.2f\n", dir);
  M5.Lcd.printf("Rotaion:\n   Roll: %7.2f\n  Pitch: %7.2f\n    Yaw: %7.2f\n",
                filter.getRoll(), filter.getPitch(), filter.getYaw());
  M5.Lcd.printf("Actual Frequency %5.2fHz",
                1000000 / (float)(now - prev_update));

  prev_update = now;
}
