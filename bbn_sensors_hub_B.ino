#include <M5Unified.h>
#include <Wire.h>
#include <ReactESP.h>  // https://github.com/mairas/ReactESP

using namespace reactesp;
ReactESP app;

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"
#include "mcu_sensors.h"

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Wire1.begin(G38, G39, 100000UL);
  Serial.begin(38400);
  mcu_sensors_scan();
}

void loop() {
  M5.update();
  mcu_sensors_update();
  app.tick();
  delay(3);
}
