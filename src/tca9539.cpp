#include <i2c_port.h>
#include <tca9539.h>

uint8_t TCA9539::readReg(uint8_t reg) {
    i2c_write(_i2c_bus, _i2c_address, &reg, 1, true);
    uint8_t ret;
    i2c_read(_i2c_bus, _i2c_address, &ret, 1, false);
    return ret;
}
void TCA9539::writeReg(uint8_t reg, uint8_t value) {
    uint8_t buf[2] = { reg, value };
    i2c_write(_i2c_bus, _i2c_address, buf, 2, false);
}

TCA9539::TCA9539(uint8_t i2c_bus, uint8_t i2c_address) {
    _i2c_bus = i2c_bus;
    _i2c_address = i2c_address;
}
uint8_t TCA9539::getInputP0() {
    return readReg(0x00);
}
uint8_t TCA9539::getInputP1() {
    return readReg(0x01);
}
void TCA9539::setOutputP0(uint8_t mask) {
    writeReg(0x02, mask);
}
void TCA9539::setOutputP1(uint8_t mask) {
    writeReg(0x03, mask);
}
void TCA9539::invertP0(uint8_t mask) {
    writeReg(0x04, mask);
}
void TCA9539::invertP1(uint8_t mask) {
    writeReg(0x05, mask);
}
void TCA9539::setConfP0(uint8_t mask) {
    writeReg(0x06, mask);
}
void TCA9539::setConfP1(uint8_t mask) {
    writeReg(0x07, mask);
}
bool TCA9539::isConnected() {
    uint8_t buf = 0x00;
    i2c_write(_i2c_bus, _i2c_address, &buf, 1, true);
    uint8_t bytesRead = i2c_read(_i2c_bus, _i2c_address, &buf, 1, false);
    if (bytesRead == 1) {
        return true;
    }
    return false;
}