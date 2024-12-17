#ifndef i2c_sensors_h
#define i2c_sensors_h

#include "i2c_sht30.h"
#include "i2c_qmp6988.h"
#include "i2c_bmp280.h"
#include "i2c_bme680.h"
#include "i2c_dht12.h"
#include "i2c_ads1115.h"
#include "i2c_bh1750fvi_tr.h"
#include "i2c_ain_4_20ma.h"
#include "i2c_sgp30.h"
#include "i2c_vl53l0x.h"
#include "i2c_ina219.h"
//#include "i2c_m5_encoder.h"

void i2c_sensors_scan(bool i2c_alt_enable_scan) {
  i2c_ads1115_try_init(&Wire, G2, G1, 100000UL);
  i2c_ina219_try_init(&Wire);
  if (i2c_alt_enable_scan) {
    i2c_ads1115_try_init(&Wire1, G38, G39, 100000UL);
    i2c_ina219_try_init(&Wire1);
  }
  i2c_bmp280_try_init();
  i2c_qmp6988_try_init();
  i2c_bme680_try_init();
  i2c_ain_4_20ma_try_init();
  i2c_dht12_try_init();
  i2c_sht30_try_init();
  i2c_sgp30_try_init();
  i2c_bh1750fvi_tr_try_init();
  i2c_vl53l0x_try_init();
  //i2c_m5_encoder_try_init(); // conflicts with ina219 on 0x40
}

void i2c_sensors_update() {
}

#endif
