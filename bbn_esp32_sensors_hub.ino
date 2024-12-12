#include <M5AtomS3.h>
#include <Wire.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"
#include "i2c_sensors.h"

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(115200);
  i2c_scan();
}

void loop() {
  delay(3);
}
