#include "m5bmm150.h"

int8_t M5Bmm150::i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                          uint16_t len) {
  if (M5.I2C.readBytes(dev_id, reg_addr, len, read_data)) {
    return BMM150_OK;
  } else {
    return BMM150_E_DEV_NOT_FOUND;
  }
}

int8_t M5Bmm150::i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                           uint16_t len) {
  if (M5.I2C.writeBytes(dev_id, reg_addr, read_data, len)) {
    return BMM150_OK;
  } else {
    return BMM150_E_DEV_NOT_FOUND;
  }
}

bool M5Bmm150::initialization(struct bmm150_dev &dev) {
  int8_t rslt = BMM150_OK;

  /* Sensor interface over SPI with native chip select line */
  dev.dev_id = 0x10;
  dev.intf = BMM150_I2C_INTF;
  dev.read = i2c_read;
  dev.write = i2c_write;
  dev.delay_ms = delay;

  rslt = bmm150_init(&dev);
  dev.settings.pwr_mode = BMM150_NORMAL_MODE;
  rslt |= bmm150_set_op_mode(&dev);
  dev.settings.preset_mode = BMM150_PRESETMODE_ENHANCED;
  rslt |= bmm150_set_presetmode(&dev);
  return rslt == BMM150_OK;
}
