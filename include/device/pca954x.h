/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#ifndef __PCA954X_H__
#define __PCA954X_H__

#include <hardware/i2c.h>

#define PCA954X_ADDRESS(A0, A1) (0b1110000 | (A1 << 1) | A0)

#define PCA9545_NONSELECTED 255

class PCA954X {
    uint gpio_reset;
    uint8_t addr;
    uint8_t port;

public:
    PCA954X(uint8_t _port, uint8_t i2c_addr, uint _gpio_reset);
    void init();
    void reset();
    int setChannel(uint8_t channel);
    uint8_t getReg();
    int setReg(uint8_t mask);
};

#endif