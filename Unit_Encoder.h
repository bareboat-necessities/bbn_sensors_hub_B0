/*!
   @brief A rotary encoder expansion From M5Stack
   @copyright Copyright (c) 2022 by M5Stack[https://m5stack.com]

   @Links [Unit Encoder](https://docs.m5stack.com/en/unit/encoder)
   @version  V0.0.2
   @date  2022-07-11
*/
#ifndef _UNIT_ENCODER_H_
#define _UNIT_ENCODER_H_

#define ENCODER_ADDR 0x40
#define ENCODER_REG  0x10
#define BUTTON_REG   0x20
#define RGB_LED_REG  0x30

class Unit_Encoder {
  private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint32_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

  public:
    void begin(TwoWire* wire = &Wire, uint8_t addr = ENCODER_ADDR,
               uint8_t sda = SDA, uint8_t scl = SCL, uint32_t speed = 200000L);
    signed short int getEncoderValue();
    bool getButtonStatus();
    void setLEDColor(uint8_t index, uint32_t color);
};

/*! @brief Initialize the Encoder. */
void Unit_Encoder::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl,
                         uint32_t speed) {
  _wire  = wire;
  _addr  = addr;
  _sda   = sda;
  _scl   = scl;
  _speed = speed;
  _wire->begin((int)_sda, (int)_scl, _speed);
}

/*! @brief Write a certain length of data to the specified register address. */
void Unit_Encoder::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                              uint8_t length) {
  _wire->beginTransmission(addr);
  _wire->write(reg);
  for (int i = 0; i < length; i++) {
    _wire->write(*(buffer + i));
  }
  _wire->endTransmission();
}

/*! @brief Read a certain length of data to the specified register address. */
void Unit_Encoder::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                             uint8_t length) {
  uint8_t index = 0;
  _wire->beginTransmission(addr);
  _wire->write(reg);
  _wire->endTransmission();
  _wire->requestFrom(addr, length);
  for (int i = 0; i < length; i++) {
    buffer[index++] = _wire->read();
  }
}

/*! @brief Read the encoder value.
    @return The value of the encoder that was read */
signed short int Unit_Encoder::getEncoderValue() {
  uint8_t data[2];
  readBytes(_addr, ENCODER_REG, data, 2);
  signed short int value = (signed short int)((data[0]) | (data[1]) << 8);
  return value;
}

/*! @brief Get the current status of the rotary encoder keys.
    @return 1 if the set was press, otherwise 0.. */
bool Unit_Encoder::getButtonStatus() {
  uint8_t data;
  readBytes(_addr, BUTTON_REG, &data, 1);
  return data;
}

/*! @brief Set the color of the LED (HEX). */
void Unit_Encoder::setLEDColor(uint8_t index, uint32_t color) {
  uint8_t data[4];
  data[3] = color & 0xff;
  data[2] = (color >> 8) & 0xff;
  data[1] = (color >> 16) & 0xff;
  data[0] = index;
  writeBytes(_addr, RGB_LED_REG, data, 4);
}

#endif
