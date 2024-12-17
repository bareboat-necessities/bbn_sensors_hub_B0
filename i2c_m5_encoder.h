#ifndef i2c_m5_encoder_h
#define i2c_m5_encoder_h

// https://docs.m5stack.com/en/unit/encoder

#include <Wire.h>
#include "Unit_Encoder.h"

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

Unit_Encoder sensor;
signed short int last_encoder_value = 0;

bool i2c_m5_encoder_try_init() {
}

#endif