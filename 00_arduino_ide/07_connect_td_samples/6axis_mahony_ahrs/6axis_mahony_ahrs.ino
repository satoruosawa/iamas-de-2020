#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

unsigned long loop_interval_micros =
    1000000UL / 25;  // = 1000000[micro sec] / 25[Hz]
unsigned long prev_loop = 0;

void setup() {
  M5.begin();
  M5.lcd.setTextSize(2);

  M5.Power.begin();
  M5.IMU.Init();

  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");

  delay(1000);
  M5.Lcd.fillScreen(BLACK);
  prev_loop = micros();
}

void loop() {
  unsigned long now = micros();
  if (now < prev_loop + loop_interval_micros) return;

  float pitch = 0.0;
  float roll = 0.0;
  float yaw = 0.0;
  M5.IMU.getAhrsData(&pitch, &roll, &yaw);

  OscWiFi.update();
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/rotaion", pitch, roll, yaw);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.println();
  M5.Lcd.printf("Rotaion:\n   Roll: %7.2f\n  Pitch: %7.2f\n    Yaw: %7.2f",
                roll, pitch, yaw);
  M5.Lcd.printf("\n\nActual Frequency %5.2fHz",
                1000000 / (float)(now - prev_loop));

  prev_loop = now;
}
