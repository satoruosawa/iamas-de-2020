#include <M5Stack.h>

#include "./m5bmm150.h"

M5Bmm150 m5Bmm150;

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
}

void setup() {
  M5.begin();
  Wire.begin(21, 22, 400000);

  if (m5Bmm150.initialize() != BMM150_OK) {
    M5.Lcd.println("BMM150 initialization failed.");
    while (1)
      ;
  }
  m5Bmm150.loadOffset();
}

void drawCompassFrame() {
  M5.Lcd.drawRect(0, 0, 160, 160, getColor(50, 50, 50));
  int center_x = 80;
  int center_y = 80;
  for (int i = 0; i < 40; i++) {
    float angle = M_PI * 2.0 / 40 * i;
    int inner = 53;
    int outer = 55;
    if (i % 5 == 0) inner = 48;
    int x0 = inner * cos(angle) + center_x;
    int x1 = outer * cos(angle) + center_x;
    int y0 = inner * sin(angle) + center_y;
    int y1 = outer * sin(angle) + center_y;
    M5.Lcd.drawLine(x0, y0, x1, y1, getColor(50, 50, 50));
  }
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(78, 10);
  M5.Lcd.print("0");
  M5.Lcd.setCursor(8, 77);
  M5.Lcd.print("90");
  M5.Lcd.setCursor(138, 77);
  M5.Lcd.print("-90");
  M5.Lcd.setCursor(60, 141);
  M5.Lcd.print("180,-180");
}

void drawCompassNeedle(float angle) {
  int center_x = 80;
  int center_y = 80;
  int x = 45 * cos((-angle - 90.0) / 180.0 * M_PI) + center_x;
  int y = 45 * sin((-angle - 90.0) / 180.0 * M_PI) + center_y;
  M5.Lcd.fillEllipse(center_x, center_y, 46, 46, BLACK);
  M5.Lcd.drawLine(center_x, center_y, x, y, WHITE);
}

void loop() {
  M5.update();
  m5Bmm150.update();
  float mag_x;
  float mag_y;
  float mag_z;
  m5Bmm150.getCalibratedData(&mag_x, &mag_y, &mag_z);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(170, 20);
  M5.Lcd.printf("Calibrated data:");
  M5.Lcd.setCursor(170, 40);
  M5.Lcd.printf("  X:%7.2f", mag_x);
  M5.Lcd.setCursor(170, 60);
  M5.Lcd.printf("  Y:%7.2f", mag_y);
  M5.Lcd.setCursor(170, 80);
  M5.Lcd.printf("  Z:%7.2f", mag_z);
  float dir = m5Bmm150.getHeadDirection();
  M5.Lcd.setCursor(170, 100);
  M5.Lcd.printf("Direction:%7.2f[deg]", dir);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 180);
  M5.Lcd.print("Press Button A to start \ncalibration.");

  drawCompassFrame();
  drawCompassNeedle(dir);

  if (M5.BtnA.wasPressed()) {
    M5.Lcd.setTextSize(2);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 110);
    M5.Lcd.print("Flip + rotate M5Stack GREY");
    m5Bmm150.calibrate(20000);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(0, 110);
    M5.Lcd.print("Done calibration.");
    delay(1000);
    M5.Lcd.clear(BLACK);
  }
  delay(100);
}