#ifndef gpio_pir_as312_h
#define gpio_pir_as312_h

#include "NmeaXDR.h"

/*
 * https://shop.m5stack.com/products/pir-module
 *
 * PIR Motion Sensor (AS312) to NMEA 0183 XDR
 */
#define PIR_MOTION_PIN G22

void gpio_pir_as312_report() {
  bool sensed = digitalRead(PIR_MOTION_PIN) == 1;
  if (sensed) {
    gen_nmea0183_xdr("$BBXDR,S,1,,PIR_MOTION", 1);
  }
}

void gpio_pir_as312_try_init() {
  pinMode(PIR_MOTION_PIN, INPUT);
  digitalRead(PIR_MOTION_PIN);
  app.onRepeat(500, []() {
    gpio_pir_as312_report();
  });
}

#endif
