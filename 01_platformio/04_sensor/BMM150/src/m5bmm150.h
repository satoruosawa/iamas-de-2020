#ifndef M5_BMM150_H__
#define M5_BMM150_H__
#include <M5Stack.h>

#include "bmm150.h"
#include "bmm150_defs.h"

class M5Bmm150 {
 public:
  static int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                         uint16_t len);
  static int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                          uint16_t len);
  bool initialization(struct bmm150_dev &dev);

 private:
};

#endif