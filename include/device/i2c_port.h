#ifndef __I2C_PORT_H__
#define __I2C_PORT_H__

#include <hardware/i2c.h>
#include <i2c_config.h>

int i2c_write(uint8_t port, uint8_t addr, uint8_t* src, size_t len, bool blocking);
int i2c_read(uint8_t port, uint8_t addr, uint8_t* dst, size_t len, bool blocking);

void initI2CBus(uint8_t port, uint gpio_sda, uint gpio_scl, uint baudrate);

void scanI2CBus(uint8_t port);

bool findI2CDevice(uint8_t port, uint8_t address, uint32_t timeout_ms = 10);

#endif