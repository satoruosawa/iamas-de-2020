#include "m5bmm150.h"

int8_t M5Bmm150::i2cRead(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                         uint16_t len) {
  if (M5.I2C.readBytes(dev_id, reg_addr, len, read_data)) {
    return BMM150_OK;
  } else {
    return BMM150_E_DEV_NOT_FOUND;
  }
}

int8_t M5Bmm150::i2cWrite(uint8_t dev_id, uint8_t reg_addr, uint8_t *read_data,
                          uint16_t len) {
  if (M5.I2C.writeBytes(dev_id, reg_addr, read_data, len)) {
    return BMM150_OK;
  } else {
    return BMM150_E_DEV_NOT_FOUND;
  }
}

int8_t M5Bmm150::initialize() {
  int8_t rslt = BMM150_OK;

  /* Sensor interface over SPI with native chip select line */
  dev_.dev_id = 0x10;
  dev_.intf = BMM150_I2C_INTF;
  dev_.read = i2cRead;
  dev_.write = i2cWrite;
  dev_.delay_ms = delay;

  /* make sure max < mag data first  */
  mag_max_.x = -2000;
  mag_max_.y = -2000;
  mag_max_.z = -2000;

  /* make sure min > mag data first  */
  mag_min_.x = 2000;
  mag_min_.y = 2000;
  mag_min_.z = 2000;

  rslt = bmm150_init(&dev_);
  dev_.settings.pwr_mode = BMM150_NORMAL_MODE;
  rslt |= bmm150_set_op_mode(&dev_);
  dev_.settings.preset_mode = BMM150_PRESETMODE_ENHANCED;
  rslt |= bmm150_set_presetmode(&dev_);
  return rslt;
}

void M5Bmm150::calibrate(uint32_t calibrate_time) {
  uint32_t calibrate_timeout = 0;

  calibrate_timeout = millis() + calibrate_time;
  Serial.printf("Go calibrate, use %d ms \r\n", calibrate_time);
  Serial.printf("running ...");

  while (calibrate_timeout > millis()) {
    bmm150_read_mag_data(&dev_);
    if (dev_.data.x) {
      mag_min_.x = (dev_.data.x < mag_min_.x) ? dev_.data.x : mag_min_.x;
      mag_max_.x = (dev_.data.x > mag_max_.x) ? dev_.data.x : mag_max_.x;
    }

    if (dev_.data.y) {
      mag_max_.y = (dev_.data.y > mag_max_.y) ? dev_.data.y : mag_max_.y;
      mag_min_.y = (dev_.data.y < mag_min_.y) ? dev_.data.y : mag_min_.y;
    }

    if (dev_.data.z) {
      mag_min_.z = (dev_.data.z < mag_min_.z) ? dev_.data.z : mag_min_.z;
      mag_max_.z = (dev_.data.z > mag_max_.z) ? dev_.data.z : mag_max_.z;
    }
    delay(100);
  }

  mag_offset_.x = (mag_max_.x + mag_min_.x) / 2;
  mag_offset_.y = (mag_max_.y + mag_min_.y) / 2;
  mag_offset_.z = (mag_max_.z + mag_min_.z) / 2;
  saveOffset();

  Serial.printf("\n calibrate finish ... \r\n");
  Serial.printf("mag_max_.x: %.2f x_min: %.2f \t", mag_max_.x, mag_min_.x);
  Serial.printf("y_max: %.2f y_min: %.2f \t", mag_max_.y, mag_min_.y);
  Serial.printf("z_max: %.2f z_min: %.2f \r\n", mag_max_.z, mag_min_.z);
}

void M5Bmm150::loadOffset() {
  if (prefs_.begin("bmm150", true)) {
    prefs_.getBytes("offset", (uint8_t *)&mag_offset_, sizeof(bmm150_mag_data));
    prefs_.end();
    Serial.printf("bmm150 load offset finish.... \r\n");
  } else {
    Serial.printf("bmm150 load offset failed.... \r\n");
  }
}

void M5Bmm150::saveOffset() {
  prefs_.begin("bmm150", false);
  prefs_.putBytes("offset", (uint8_t *)&mag_offset_, sizeof(bmm150_mag_data));
  prefs_.end();
}

void M5Bmm150::update() { bmm150_read_mag_data(&dev_); }

bmm150_mag_data M5Bmm150::getRawData() { return dev_.data; }

void M5Bmm150::getCalibratedData(float *mx, float *my, float *mz) {
  *mx = dev_.data.x - mag_offset_.x;
  *my = dev_.data.y - mag_offset_.y;
  *mz = dev_.data.z - mag_offset_.z;
}

float M5Bmm150::getHeadDirection() {
  return atan2(dev_.data.x - mag_offset_.x, dev_.data.y - mag_offset_.y) *
         180.0 / M_PI;
}
