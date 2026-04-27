#ifndef __TCA9539_H__
#define __TCA9539_H__

#include <stdint-gcc.h>
class TCA9539 {
    uint8_t _i2c_bus;
    uint8_t _i2c_address;
    uint8_t readReg(uint8_t reg);
    void writeReg(uint8_t reg, uint8_t value);

public:
    TCA9539(uint8_t i2c_bus, uint8_t i2c_address);
    uint8_t getInputP0();
    uint8_t getInputP1();
    void setOutputP0(uint8_t mask);
    void setOutputP1(uint8_t mask);
    void invertP0(uint8_t mask);
    void invertP1(uint8_t mask);
    void setConfP0(uint8_t mask);
    void setConfP1(uint8_t mask);

    bool isConnected();

};

#endif