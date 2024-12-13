#ifndef i2c_bme680_h
#define i2c_bme680_h

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

#define BME680_I2C_ADDRESS (0x77)    // The default I2C address

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 i2c_bme680_sensor(&Wire); // I2C
bool i2c_bme680_found = false;

void i2c_bme680_report() {
  if (bme680.performReading()) {
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_BME680", bme680.temperature);             // C
    gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_BME680", bme680.pressure);                // Pa
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_BME680", bme680.humidity);                // %
    gen_nmea0183_xdr("$BBXDR,H,%.2f,,GASR_BME680", bme680.gas_resistance / 1000.0);  // KOhms
  }
}

void i2c_bme680_try_init() {
  for (int i = 0; i < 3; i++) {
    i2c_bme680_found = i2c_bme680_sensor.begin(BME680_I2C_ADDRESS);
    if (i2c_bme680_found) {
      break;
    }
    delay(10);
  }
  if (i2c_bme680_found) {
    gen_nmea0183_msg("$BBTXT,01,01,01,ENVIRONMENT found bme680 sensor at address=0x%s", String(BME680_I2C_ADDRESS, HEX).c_str());
    // Set up oversampling and filter initialization
    bme680.setTemperatureOversampling(BME680_OS_8X);
    bme680.setHumidityOversampling(BME680_OS_2X);
    bme680.setPressureOversampling(BME680_OS_4X);
    bme680.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme680.setGasHeater(320, 150); // 320*C for 150 ms
    app.onRepeat(5000, []() {
      i2c_bme680_report();
    });
  }
}

#endif
