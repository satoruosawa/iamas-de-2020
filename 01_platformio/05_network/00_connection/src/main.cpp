#include <M5Stack.h>
#include <WiFi.h>

#include "./wifi-info.h"

const String SSID = WIFI_SSID;          // "xxxx"
const String PASSWORD = WIFI_PASSWORD;  // "xxxx"

void setup() {
  M5.begin();
  M5.lcd.setTextSize(2);
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println(" connected.");
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());
}

void loop() {}
