#define M5STACK_MPU6886

#include <M5Stack.h>

unsigned long last_wakeup;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.IMU.Init();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
}

void loop() {
  float acc_x, acc_y, acc_z;
  M5.IMU.getAccelData(&acc_x, &acc_y, &acc_z);

  if (abs(acc_z - 1.0) > 0.2) {
    last_wakeup = millis();
  }
  M5.Lcd.setCursor(0, 0);
  if (millis() - last_wakeup > 5000) {
    M5.Lcd.print("Rest");
  } else {
    M5.Lcd.print("Wake");
  }

  delay(1);
}