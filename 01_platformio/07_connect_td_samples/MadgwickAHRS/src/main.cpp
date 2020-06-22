#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>
#include <MadgwickAHRS.h>
#include <Wire.h>

#include "./m5bmm150.h"
#include "./wifi-info.h"

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

M5Bmm150 m5Bmm150;
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
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  delay(1000);
  M5.Lcd.fillScreen(BLACK);
  prev_update = micros();
}

void loop() {
  if (micros() - prev_update < loop_interval) return;
  prev_update = micros();
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  filter.updateIMU(gyroX, gyroY, gyroZ, accX, accY, accZ);
  m5Bmm150.update();
  float dir = m5Bmm150.getHeadDirection();
  OscWiFi.update();
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/gyro", gyroX, gyroY, gyroZ);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/rotaion", filter.getPitch(),
               filter.getRoll(), filter.getYaw());
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/direction", dir);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.println();
  M5.Lcd.printf("Gyro:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", gyroX, gyroY,
                gyroZ);
  M5.Lcd.printf("Rotaion:\n  Pitch: %7.2f\n  Roll: %7.2f\n  Yaw: %7.2f\n",
                filter.getPitch(), filter.getRoll(), filter.getYaw());
  M5.Lcd.printf("direction: %7.2f ", dir);
}
