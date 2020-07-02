#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>
#include <MadgwickAHRS.h>

#include "./wifi-info.h"

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

Madgwick filter;

unsigned long loop_interval_microsec, prev_loop;
int sampling_freq = 10;  // Hz

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();
  loop_interval_microsec = 1000000 / sampling_freq;
  filter.begin(sampling_freq);

  M5.lcd.setTextSize(2);
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  delay(100);
  M5.Lcd.clear(BLACK);
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
  OscWiFi.update();
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/gyro", gyro_x, gyro_y,
               gyro_z);
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/rotaion", filter.getPitch(),
               filter.getRoll(), filter.getYaw());

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.println();
  M5.Lcd.printf("Rotaion:\n   Roll: %7.2f\n  Pitch: %7.2f\n    Yaw: %7.2f\n",
                filter.getRoll(), filter.getPitch(), filter.getYaw());
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_loop));
  prev_loop = now;
}
