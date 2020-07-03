#ifndef M5_BMM150_H__
#define M5_BMM150_H__
#include <M5Stack.h>

#include "Preferences.h"
#include "bmm150.h"
#include "bmm150_defs.h"

class M5Bmm150 {
 public:
  static int8_t i2cRead(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                        uint16_t len);
  static int8_t i2cWrite(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                         uint16_t len);
  int8_t initialize();
  void calibrate(uint32_t calibrate_time);
  void loadOffset();
  void saveOffset();
  void update();
  bmm150_mag_data getRawData();
  void getCalibratedData(float *mx, float *my, float *mz);
  float getHeadDirection();

 private:
  Preferences prefs_;

  bmm150_mag_data mag_offset_;
  bmm150_mag_data mag_max_;
  bmm150_mag_data mag_min_;
  struct bmm150_dev dev_;
};

#endif