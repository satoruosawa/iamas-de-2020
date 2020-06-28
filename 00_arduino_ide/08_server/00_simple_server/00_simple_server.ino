#include <ESPmDNS.h>
#include <M5Stack.h>
#include <WebServer.h>
#include <WiFi.h>

const String SSID = WIFI_SSID;          // "xxxx"
const String PASSWORD = WIFI_PASSWORD;  // "xxxx"

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from M5Stack!");
  M5.Lcd.println("accessed on \"/\"");
}

void handleNotFound() {
  server.send(404, "text/plain", "File Not Found\n\n");
  M5.Lcd.println("File Not Found");
}

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

  if (MDNS.begin("m5stack")) {
    M5.Lcd.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  M5.Lcd.println("HTTP server started");
}

void loop() { server.handleClient(); }
