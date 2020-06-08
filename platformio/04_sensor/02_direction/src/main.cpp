#include <M5Stack.h>
#include <Wire.h>

#include "m5bmm150.h"

M5Bmm150 m5Bmm150;
struct bmm150_dev dev;

void setup() {
  M5.begin();
  Wire.begin(21, 22, 400000);

  if (!m5Bmm150.initialization(dev)) {
    Serial.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  M5.Lcd.setTextSize(2);
}

void loop() {
  bmm150_read_mag_data(&dev);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("x: ");
  M5.Lcd.print(dev.data.x);
  M5.Lcd.print(",y: ");
  M5.Lcd.print(dev.data.y);
  M5.Lcd.print(",z: ");
  M5.Lcd.println(dev.data.z);

  delay(100);
}