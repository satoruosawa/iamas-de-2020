#include <M5Stack.h>
#include <Wire.h>

#include "m5bmm150.h"

M5Bmm150 m5Bmm150 = M5Bmm150();
struct bmm150_dev dev;

void setup() {
  M5.begin();
  Wire.begin(21, 22, 400000);

  if (!m5Bmm150.initialization(dev)) {
    Serial.println("BMM150 initialization failed.");
    while (1)
      ;
  }
}

void loop() {
  bmm150_read_mag_data(&dev);
  Serial.print("x: ");
  Serial.print(dev.data.x);
  Serial.print(",y: ");
  Serial.print(dev.data.y);
  Serial.print(",z: ");
  Serial.println(dev.data.z);

  delay(100);
}