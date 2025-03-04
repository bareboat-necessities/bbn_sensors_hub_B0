#ifndef gpio_limit_switch_h
#define gpio_limit_switch_h

#include "NmeaXDR.h"

#define LIMIT_SWITCH_PIN G19

struct LimitSwitch {
  bool reached = false;
  unsigned long last_limit_reported = 0UL;
};

LimitSwitch limit_switch;

void gpio_limit_switch_report() {
  bool reached = !digitalRead(LIMIT_SWITCH_PIN);
  if (reached != limit_switch.reached) {
    limit_switch.reached = reached;
    if (reached) {
      gen_nmea0183_xdr("$BBXDR,S,1,,LIMIT_NEW", 1);
    } else {
      gen_nmea0183_xdr("$BBXDR,S,0,,LIMIT_NEW", 0);
    }
    limit_switch.last_limit_reported = millis();
  }
  if (millis() - limit_switch.last_limit_reported > 5000) {
    if (limit_switch.reached) {
      gen_nmea0183_xdr("$BBXDR,S,1,,LIMIT_CUR", 1);
    } else {
      gen_nmea0183_xdr("$BBXDR,S,0,,LIMIT_CUR", 0);
    }
    limit_switch.last_limit_reported = millis();
  }
}

void gpio_limit_switch_try_init() {
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  limit_switch.reached = !digitalRead(LIMIT_SWITCH_PIN);
  app.onRepeat(50, []() {
    gpio_limit_switch_report();
  });
}

#endif
