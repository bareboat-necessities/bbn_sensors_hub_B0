#include <M5AtomS3.h>
#include <Arduino.h>
#include <M5Unified.h>
#include <I2C_Class.h>
#include <Wire.h>
#include <ReactESP.h>  // https://github.com/mairas/ReactESP

using namespace reactesp;
ReactESP app;

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"
#include "i2c_sensors.h"

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin(G2, G1, 400000U);
  Serial.begin(115200);
  i2c_sensors_scan();
}

void loop() {
  AtomS3.update();
  i2c_sensors_update();
  app.tick();
  delay(3);
}
