#ifndef i2c_sensors_h
#define i2c_sensors_h

#include <M5Unified.h>
#include <M5UnitUnified.h>

#include "i2c_ads1115.h"
#include "i2c_sht30.h"
#include "i2c_qmp6988.h"

void i2c_sensors_scan() {
  i2c_ads1115_try_init();
  i2c_sht30_try_init();
  i2c_qmp6988_try_init();
}

void i2c_sensors_update() {
  Units.update();
}

#endif
