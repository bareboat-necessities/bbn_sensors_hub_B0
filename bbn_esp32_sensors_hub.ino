#include <M5AtomS3.h>
#include <Wire.h>
#include <ReactESP.h>  // https://github.com/mairas/ReactESP

using namespace reactesp;
ReactESP app;

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"
#include "w1_sensors.h"
#include "i2c_sensors.h"

bool i2c_alt_enable = true;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin(G2, G1, 100000UL);
  if (i2c_alt_enable) {
    Wire1.begin(G38, G39, 100000UL);
  }
  Serial.begin(115200);
  one_wire_sensors_scan();
  i2c_sensors_scan(i2c_alt_enable);
}

void loop() {
  AtomS3.update();
  i2c_sensors_update();
  app.tick();
  delay(3);
}
