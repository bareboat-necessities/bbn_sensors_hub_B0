#ifndef i2c_m5_encoder_h
#define i2c_m5_encoder_h

// https://docs.m5stack.com/en/unit/encoder

#include <Wire.h>
#include "Unit_Encoder.h"

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

#define ENCODER_I2C_ADDR (0x40)

Unit_Encoder i2c_m5_encoder_sensor;
signed short int i2c_m5_encoder_last_value = 0;

void i2c_m5_encoder_report() {
  signed short int encoder_value = i2c_m5_encoder_sensor.getEncoderValue();
  bool btn_status                = i2c_m5_encoder_sensor.getButtonStatus();
  if (i2c_m5_encoder_last_value != encoder_value) {
    gen_nmea0183_xdr("$BBXDR,S,%.0f,,ENCODER_ADJ", (float)encoder_value);
    if (i2c_m5_encoder_last_value < encoder_value) {
      i2c_m5_encoder_sensor.setLEDColor(1, 0x00FF00);
    } else {
      i2c_m5_encoder_sensor.setLEDColor(2, 0xFF0000);
    }
    i2c_m5_encoder_last_value = encoder_value;
  } else {
    i2c_m5_encoder_sensor.setLEDColor(0, 0x0000FF);
  }
  if (!btn_status) {
    gen_nmea0183_xdr("$BBXDR,S,%.0f,,ENCODER_SET", (float)encoder_value);
    i2c_m5_encoder_sensor.setLEDColor(0, 0xFFFF00);
  }
}

bool i2c_m5_encoder_try_init() {
  bool i2c_m5_encoder_found = false;
  for (int i = 0; i < 3; i++) {
    Wire.beginTransmission(ENCODER_I2C_ADDR);
    i2c_m5_encoder_found = !Wire.endTransmission();
    if (i2c_m5_encoder_found) {
      i2c_m5_encoder_sensor.begin(&Wire, ENCODER_I2C_ADDR, G2, G1, 100000U);
      break;
    }
    delay(4);
  }
  if (i2c_m5_encoder_found) {
    gen_nmea0183_msg("$BBTXT,01,01,01,LOGIC found m5_encoder sensor at address=0x%s", String(ENCODER_I2C_ADDR, HEX).c_str());
    app.onRepeat(250, []() {
      i2c_m5_encoder_report();
    });
  }
  return i2c_m5_encoder_found;
}

#endif