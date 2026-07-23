/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

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