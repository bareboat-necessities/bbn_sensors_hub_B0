#include <M5AtomS3.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(115200);
}

void loop() {
  delay(3);
}
