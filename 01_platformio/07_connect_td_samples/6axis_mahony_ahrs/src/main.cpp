#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>

#include "./wifi-info.h"

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

unsigned long loop_interval_micros = 1000000UL / 25;  // 25Hz
unsigned long prev_update;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
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
}

void loop() {
  unsigned long now = micros();
  if (now < prev_update + loop_interval_micros) return;
  prev_update = now;
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);
  OscWiFi.update();
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/gyro", gyroX, gyroY, gyroZ);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/rotaion", pitch, roll, yaw);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.println();
  M5.Lcd.printf("Gyro:\n  X: %7.2f\n  Y: %7.2f\n  Z: %7.2f\n", gyroX, gyroY,
                gyroZ);
  M5.Lcd.printf("Rotaion:\n  Pitch: %7.2f\n  Roll: %7.2f\n  Yaw: %7.2f", pitch,
                roll, yaw);
}
