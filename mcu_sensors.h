#ifndef mcu_sensors_h
#define mcu_sensors_h

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
#include "gpio_tds_cqrsentds01.h"
#include "gpio_240_30_ohm_sensor.h"

void mcu_sensors_scan() {
  i2c_ina219_try_init(&Wire);
  i2c_ads1115_try_init(&Wire, G26, G32, 100000UL);
  i2c_ain_4_20ma_try_init(&Wire, G26, G32, 100000UL);
  i2c_bmp280_try_init();
  i2c_qmp6988_try_init();
  i2c_bme680_try_init();
  i2c_dht12_try_init();
  i2c_sgp30_try_init();
  i2c_bh1750fvi_tr_try_init();
  i2c_vl53l0x_try_init();
  gpio_tds_cqrsentds01_try_init();
  gpio_240_30_ohm_try_init();
}

void mcu_sensors_update() {
}

#endif
