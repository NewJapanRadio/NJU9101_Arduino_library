#include "NJU9101.h"

NJU9101Class NJU9101;

NJU9101Class::NJU9101Class(uint8_t slvAddrBase) {
  this->slaveAddress = slvAddrBase;
}

NJU9101Class::~NJU9101Class() {
}

void NJU9101Class::begin(uint8_t slvAddr) {
  this->slaveAddress |= (slvAddr & 0x07);
  Wire.begin();
}

void NJU9101Class::end() {
}

void NJU9101Class::read(Address address, uint8_t data[], size_t length) {
  Wire.beginTransmission(this->slaveAddress);
  Wire.write((uint8_t)address);
  Wire.endTransmission(false);
  Wire.requestFrom(this->slaveAddress, (uint8_t)length, (uint8_t)false);
  for (int i = 0; i < length; i++) {
    data[i] = Wire.read();
  }
  Wire.endTransmission(true);
}

void NJU9101Class::write(Address address, uint8_t data[], size_t length) {
  Wire.beginTransmission(this->slaveAddress);
  Wire.write((uint8_t)address);
  for (int i = 0; i < length; i++) {
    Wire.write(data[i]);
  }
  Wire.endTransmission(true);
}

bool NJU9101Class::reset() {
  uint8_t wd = CTRL_RST;
  uint8_t rd = 0;
  NJU9101Class::write(NJU9101_ADDRESS_CTRL, &wd, 1);
  // wait for boot
  do {
    NJU9101Class::read(NJU9101_ADDRESS_STATUS, &rd, 1);
    if (rd == 0xff) {
      // I2C read will be failed.
      return false;
    }
  } while (rd & STATUS_BOOT);
  return true;
}

bool NJU9101Class::awake_osc() {
  uint8_t wd = BLKCTRL_OSC_POWER_DOWN_NEVER;
  uint8_t rd = 0;
  NJU9101Class::write(NJU9101_ADDRESS_BLKCTRL, &wd, 1);
  // wait for wake up
  do {
    NJU9101Class::read(NJU9101_ADDRESS_STATUS, &rd, 1);
    if (rd == 0xff) {
      // I2C read will be failed.
      return false;
    }
  } while ((rd & STATUS_CLKRUN) == 0);
  return true;
}

bool NJU9101Class::wait_eoc() {
  uint8_t rd = 0;
  do {
    NJU9101Class::read(NJU9101_ADDRESS_STATUS, &rd, 1);
    if (rd == 0xff) {
      // I2C read will be failed.
      return false;
    }
  } while (rd & STATUS_RDYB);
  return true;
}
