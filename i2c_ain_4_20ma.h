#ifndef i2c_ain_4_20ma_h
#define i2c_ain_4_20ma_h

#include <Wire.h>

#include "MODULE_4_20MA.h"
#include "NmeaXDR.h"
#include "NmeaChecksum.h"

MODULE_4_20MA i2c_ain_4_20ma_sensor;

void i2c_ain_4_20ma_report() {
  gen_nmea0183_xdr("$BBXDR,I,%.5f,A,AMPS", (float)(i2c_ain_4_20ma_sensor.getCurrentValue(0)) / 100.0 / 1000.0);  // Amp
}

bool i2c_ain_4_20ma_try_init() {
  bool i2c_ain_4_20ma_found = false;
  for (int i = 0; i < 3; i++) {
    i2c_ain_4_20ma_found = i2c_ain_4_20ma_sensor.begin(&Wire, MODULE_4_20MA_ADDR, G2, G1, 100000UL);
    if (i2c_ain_4_20ma_found) {
      break;
    }
    delay(10);
  }
  if (i2c_ain_4_20ma_found) {
    gen_nmea0183_msg("$BBTXT,01,01,01,ELECTRIC found 4-20mAmp sensor at address=0x%s", String(MODULE_4_20MA_ADDR, HEX).c_str());
    app.onRepeat(5000, []() {
      i2c_ain_4_20ma_report();
    });
  }
  return i2c_ain_4_20ma_found;
}

#endif
