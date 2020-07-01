#include <M5Stack.h>
#include <WiFi.h>

// Wi-Fiの設定
const String SSID = WIFI_SSID;          // 各自のSSIDに変更 "ssid"
const String PASSWORD = WIFI_PASSWORD;  // 各自のWiFiパスワードに変更 "pass"

void setup() {
  M5.begin();
  M5.lcd.setTextSize(2);

  // WiFi へ接続開始
  WiFi.begin(SSID.c_str(), PASSWORD.c_str());
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
