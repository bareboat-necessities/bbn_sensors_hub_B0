#ifndef i2c_as3935_h
#define i2c_as3935_h

#include <Wire.h>
#include <SparkFun_AS3935.h>

#include "NmeaXDR.h"
#include "NmeaChecksum.h"

// 0x03 is default i2c address, but the address can also be 0x02, 0x01.
// Adjust the address jumpers on the underside of the product.
// C - SCL i2c clock
// D - SDA i2c data
#define AS3935_I2C_ADDR 0x03
#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

SparkFun_AS3935 i2c_as3935_sensor(AS3935_I2C_ADDR);

// Interrupt pin for lightning detection
const int lightningInt = G7;

byte noiseFloor = 4;
byte watchDogVal = 3;
byte spike = 2;
byte lightningThresh = 0;

void i2c_as3935_report() {
  if (digitalRead(lightningInt) == HIGH) {
    // Hardware has alerted us to an event, now we read the interrupt register
    // to see exactly what it is.
    uint8_t intVal = i2c_as3935_sensor.readInterruptReg();
    if (intVal == NOISE_INT) {
      // Noise Detected!
      //Serial.println("Noise Detected!");
    }
    else if (intVal == DISTURBER_INT) {
      // Disturber Detected!
      //Serial.println("Disturber Detected!");
    }
    else if (intVal == LIGHTNING_INT) {
      //Serial.println("Lightning Strike Detected!");
      // Lightning! Now how far away is it? Distance estimation takes into
      // account any previously seen events in the last 15 seconds.
      gen_nmea0183_xdr("$BBXDR,D,%.0f,M,LIGHTNING_RANGE", (float)i2c_as3935_sensor.distanceToStorm() * 1000.0);
      gen_nmea0183_xdr("$BBXDR,X,%.0f,,LIGHTNING_LEVEL", (float)i2c_as3935_sensor.lightningEnergy());
    }
  }
}

bool i2c_as3935_try_init() {
  bool i2c_as3935_found = false;
  pinMode(lightningInt, INPUT); // When lightning is detected the interrupt pin goes HIGH.

  i2c_as3935_found = i2c_as3935_sensor.begin(Wire1);
  if (i2c_as3935_found) {
    i2c_as3935_sensor.maskDisturber(true);
    i2c_as3935_sensor.setNoiseLevel(noiseFloor);
    //i2c_as3935_sensor.watchdogThreshold(watchDogVal);
    //i2c_as3935_sensor.spikeRejection(spike);
    //i2c_as3935_sensor.lightningThreshold(lightningThresh);
    i2c_as3935_sensor.setIndoorOutdoor(INDOOR);
    //i2c_as3935_sensor.setIndoorOutdoor(OUTDOOR);
    gen_nmea0183_msg("$BBTXT,01,01,01,ENVIRONMENT found as3935 sensor at address=0x%s", String(AS3935_I2C_ADDR, HEX).c_str());
    app.onRepeat(100, []() {
      i2c_as3935_report();
    });
  }
  return i2c_as3935_found;
}

#endif

