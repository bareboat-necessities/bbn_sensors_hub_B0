#ifndef i2c_bmp280_h
#define i2c_bmp280_h

#include <M5UnitENV.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

BMP280 i2c_bmp280_sensor;
bool i2c_bmp280_found = false;

void i2c_bmp280_report() {
  if (i2c_bmp280_sensor.update()) {
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_BMP280", i2c_bmp280_sensor.cTemp);        // C
    gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_BMP280", i2c_bmp280_sensor.pressure);     // Pa
  }
}

#endif
