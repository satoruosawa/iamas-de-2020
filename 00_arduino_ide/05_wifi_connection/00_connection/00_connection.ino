#include <M5Stack.h>
#include <WiFi.h>

const String SSID = WIFI_SSID;          // WIFI_SSIDを変更
const String PASSWORD = WIFI_PASSWORD;  // WIFI_PASSWORDを変更

void setup() {
  M5.begin();
  M5.lcd.setTextSize(2);

  WiFi.begin(SSID.c_str(), PASSWORD.c_str());  // WiFi へ接続開始
  M5.Lcd.printf("Connecting to the WiFi AP: %s ", SSID.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    // 接続完了までループ
    delay(500);
    M5.Lcd.print(".");
  }
  // 接続完了

  M5.Lcd.println(" connected.");
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());
}

void loop() {}
