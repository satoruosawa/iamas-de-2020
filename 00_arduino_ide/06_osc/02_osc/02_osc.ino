#include <ArduinoOSC.h>
#include <M5Stack.h>

const String SSID = WIFI_SSID;            // "xxxx"
const String PASSWORD = WIFI_PASSWORD;    // "xxxx"
const String TARGEET_IP = PC_IP_ADDRESS;  // "0.0.0.0"
const int TARGET_PORT = 10000;

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

void loop() {
  OscWiFi.update();
  float second = millis() / 1000.0;
  OscWiFi.send(TARGEET_IP.c_str(), TARGET_PORT, "/test", second);

  M5.Lcd.setCursor(0, 120);
  M5.Lcd.println("Send OSC");
  M5.Lcd.print("Target IP: ");
  M5.Lcd.println(TARGEET_IP.c_str());
  M5.Lcd.print("Target Port: ");
  M5.Lcd.println(TARGET_PORT);
  M5.Lcd.print("Value: ");
  M5.Lcd.println(second);
  delay(10);
}
