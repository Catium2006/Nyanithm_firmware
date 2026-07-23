/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#ifndef __WS2812_H__
#define __WS2812_H__

#include <stdint-gcc.h>

#include "ws2812.pio.h"

typedef uint32_t GRB24;

class WS2812 {
private:
    uint _sm;
    PIO _pio;
    uint32_t _pin;
    uint32_t _count;
    GRB24* _buffer;

    inline void sendGRB24(GRB24 raw);

public:
    WS2812(PIO pio, uint sm, uint32_t pin, uint32_t count);
    ~WS2812();

    void setColor(uint32_t index, uint8_t r, uint8_t g, uint8_t b);

    void fill(uint8_t r, uint8_t g, uint8_t b);

    void flush();
};

#endif