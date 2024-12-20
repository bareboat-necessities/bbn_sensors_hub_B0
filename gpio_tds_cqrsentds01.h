#ifndef gpio_tds_cqrsentds01_h
#define gpio_tds_cqrsentds01_h

#include "NmeaXDR.h"
#include "CQRobotTDS.h"

/*
  TDS sensor is connected to analog pin G7
*/
int TDS_pin = G7;
CQRobotTDS tds_sensor(TDS_pin, 3.3, 4096.0 /* For ESP32 built-in 12bit ADC */);

void gpio_tds_cqrsentds01_report() {
  float temp = 25.0; // TODO: read temperature from a real sensor
  float tdsValuePPM = tds_sensor.update(temp);
  gen_nmea0183_xdr("$BBXDR,X,%.4f,S,TDS", (float)(tdsValuePPM * 0.001));        // Parts per Thousand
}

void gpio_tds_cqrsentds01_try_init() {
  pinMode(TDS_pin, INPUT);
  app.onRepeat(2000, []() {
    gpio_tds_cqrsentds01_report();
  });
}

#endif
