#include <M5Stack.h>
#include <Wire.h>

#include "./m5bmm150.h"

M5Bmm150 m5Bmm150;

void setup() {
  M5.begin();
  Wire.begin(21, 22, 400000);

  if (m5Bmm150.initialize() != BMM150_OK) {
    Serial.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5Bmm150.loadOffset();
  M5.Lcd.setTextSize(2);
}

void loop() {
  m5Bmm150.update();
  bmm150_mag_data data = m5Bmm150.getRawData();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Raw data:\n");
  M5.Lcd.printf("  x: %8.2f\n", data.x);
  M5.Lcd.printf("  y: %8.2f\n", data.y);
  M5.Lcd.printf("  z: %8.2f\n", data.z);
  float dir = m5Bmm150.getHeadDirection();
  M5.Lcd.printf("direction: %7.2f[deg]", dir);
  delay(100);
}