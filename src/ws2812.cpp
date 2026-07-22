#include <pico/stdlib.h>

#include "ws2812.h"

WS2812::WS2812(PIO pio, uint sm, uint32_t pin, uint32_t count) {
    _pio = pio;
    _sm = sm;
    _pin = pin;
    _count = count;
    _buffer = new GRB24[_count];
    uint offset = pio_add_program(_pio, &ws2812_program);
    pio_gpio_init(_pio, _pin);
    pio_sm_set_consecutive_pindirs(_pio, _sm, _pin, 1, true);
    pio_sm_config c = ws2812_program_get_default_config(offset);
    sm_config_set_set_pins(&c, _pin, 1);
    sm_config_set_out_shift(&c, false, true, 24);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    sm_config_set_clkdiv(&c, 5.0); // 5 分频
    pio_sm_init(_pio, _sm, offset, &c);
    pio_sm_set_enabled(_pio, _sm, true);
}

WS2812::~WS2812() {
    delete _buffer;
}

void WS2812::sendGRB24(GRB24 raw) {
    pio_sm_put_blocking(_pio, _sm, raw << 8);
}

void WS2812::setColor(uint32_t index, uint8_t r, uint8_t g, uint8_t b) {
    _buffer[index] = (g << 16) | (r << 8) | b;
}

void WS2812::fill(uint8_t r, uint8_t g, uint8_t b) {
    for(uint i = 0; i < _count; i++) {
        setColor(i, r, g, b);
    }
}

void WS2812::flush() {
    for(uint i = 0; i < _count; i++) {
        sendGRB24(_buffer[i]);
    }
}
