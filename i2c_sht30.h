#ifndef i2c_sht30_h
#define i2c_sht30_h

#include <M5Unified.h>
#include <M5UnitUnified.h>
#include <M5UnitUnifiedENV.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

m5::unit::UnitSHT30 i2c_sht30_sensor;
bool i2c_sht30_found = false;

void i2c_sht30_report() {
  if (i2c_sht30_sensor.updated()) {
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_SHT3X", i2c_sht30_sensor.humidity());   // %
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_SHT3X", i2c_sht30_sensor.cTemp());      // C
  }
}

void i2c_sht30_try_init() {
  for (int i = 0; i < 3; i++) {
    i2c_sht30_found = i2c_sht30_sensor.begin(&Wire, SHT3X_I2C_ADDR, G2, G1, 100000U);
    if (i2c_sht30_found) {
      break;
    }
    delay(20);
  }
  if (i2c_sht30_found) {
    gen_nmea0183_msg("$BBTXT,01,01,01,ENVIRONMENT found sht30 sensor at address=0x%s", String(SHT3X_I2C_ADDR, HEX).c_str());
    app.onRepeat(5000, []() {
      i2c_sht30_report();
    });
  }
}

#endif
