#define M5STACK_MPU6886

#include <ArduinoOSC.h>
#include <M5Stack.h>

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

float accX = 0.0;
float accY = 0.0;
float accZ = 0.0;

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
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  OscWiFi.update();
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/acceleration", accX, accY,
               accZ);

  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.printf("acceleration: (%5.2f, %5.2f, %5.2f) ", accX, accY, accZ);
  delay(10);
}
