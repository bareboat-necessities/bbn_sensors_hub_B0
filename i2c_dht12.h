#ifndef i2c_dht12_h
#define i2c_dht12_h

#include <M5UnitENV.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

DHT12 i2c_dht12_sensor;
bool i2c_dht12_found = false;

void i2c_dht12_report() {
  if (i2c_dht12_sensor.update()) {
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_DHT12", i2c_dht12_sensor.humidity);   // %
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_DHT12", i2c_dht12_sensor.cTemp);      // C
  }
}

#endif
