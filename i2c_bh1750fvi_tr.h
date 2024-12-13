#ifndef i2c_bh1750fvi_tr_h
#define i2c_bh1750fvi_tr_h

#include <Wire.h>
#include <M5_DLight.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

#define BH1750FVI_TR_I2C_ADDR 0x23

M5_DLight i2c_bh1750fvi_tr_sensor(BH1750FVI_TR_I2C_ADDR);
bool i2c_bh1750fvi_tr_found = false;

void i2c_bh1750fvi_tr_report() {
  uint16_t lux = i2c_bh1750fvi_tr_sensor.getLUX();
  gen_nmea0183_xdr("$BBXDR,X,%.1f,L,ILLU", (float)lux);
}

void i2c_bh1750fvi_tr_try_init() {
  for (int i = 0; i < 3; i++) {
    i2c_bh1750fvi_tr_found = i2c_bh1750fvi_tr_sensor.begin();
    if (i2c_bh1750fvi_tr_found) {
      break;
    }
    delay(10);
  }
  if (i2c_bh1750fvi_tr_found) {
    gen_nmea0183_msg("$BBTXT,01,01,01,ENVIRONMENT found bh1750fvi-tr sensor at address=0x%s", String(BH1750FVI_TR_I2C_ADDR, HEX).c_str());
    app.onRepeat(2000, []() {
      i2c_bh1750fvi_tr_report();
    });
  }
}

#endif



