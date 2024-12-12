#ifndef i2c_sensors_h
#define i2c_sensors_h

#include "i2c_ads1115.h"

void i2c_sensors_scan() {
  i2c_ads1115_try_init();
}

void i2c_sensors_update() {
}

#endif
