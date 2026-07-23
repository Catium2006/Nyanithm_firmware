/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#include <debug.h>
#include <hardware/i2c.h>
#include <i2c_config.h>
#include <i2c_port.h>
#include <pico/stdlib.h>

uint I2C_SDA[2] = { 0, 4 };
uint I2C_SCL[2] = { 1, 5 };

int i2c_write(uint8_t port, uint8_t addr, uint8_t* src, size_t len, bool blocking) {
#if HWI2C
    if (port == 0)
        return i2c_write_blocking(i2c0, addr, src, len, blocking);
    if (port == 1)
        return i2c_write_blocking(i2c1, addr, src, len, blocking);
#else

#endif
}
int i2c_read(uint8_t port, uint8_t addr, uint8_t* dst, size_t len, bool blocking) {
#if HWI2C
    if (port == 0)
        return i2c_read_blocking(i2c0, addr, dst, len, blocking);
    if (port == 1)
        return i2c_read_blocking(i2c1, addr, dst, len, blocking);
#else

#endif
}

void initI2CBus(uint8_t port, uint gpio_sda, uint gpio_scl, uint baudrate) {
    I2C_SDA[port] = gpio_sda;
    I2C_SCL[port] = gpio_scl;
#if HWI2C
    int br;
    // I2C Initialisation
    if (port == 0)
        br = i2c_init(i2c0, baudrate);
    if (port == 1)
        br = i2c_init(i2c1, baudrate);
#if ENABLE_DEBUG
    // printf("baudrate:%d\n", br);
#endif
    gpio_set_function(gpio_sda, GPIO_FUNC_I2C);
    gpio_set_function(gpio_scl, GPIO_FUNC_I2C);
    gpio_pull_up(gpio_sda);
    gpio_pull_up(gpio_scl);
#else
#warning Using Software I2C Interface
    gpio_init(gpio_sda);
    gpio_init(gpio_scl);
    gpio_pull_up(gpio_sda);
    gpio_pull_up(gpio_scl);
#endif
}

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void scanI2CBus(uint8_t port) {
    // printf("I2C Bus Scan\n");
    uint8_t total_devices = 0;
    for (int addr = 0; addr < (1 << 7); addr++) {

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read(port, addr, &rxdata, 1, false);

        if (ret >= 0) {
            printf("device at 0x%02x\n", addr);
            total_devices++;
        }
    }
    printf("%d devices found\n", total_devices);
    printf("Done.\n");
}

bool findI2CDevice(uint8_t port, uint8_t address,uint32_t timeout_ms) {
    uint8_t buf[1];
    for(int i  = 0 ; i < timeout_ms ; i++){
        if(i2c_read(port, address, buf, 1, false) >= 0){
            return true;
        }
        sleep_ms(1);
    }
    return false;
}