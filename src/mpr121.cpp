/* Modified from https://github.com/adafruit/Adafruit_MPR121 */

#include <mpr121.h>

#include <stdio.h>

#include <hardware/i2c.h>

#include <debug.h>
#include <i2c_port.h>

/*!
 *  @brief    Begin an MPR121 object on a given I2C bus. This function resets
 *            the device and writes the default settings.
 *  @param    port
 *            I2C port which is going to be used
 *  @param    i2c_addr
 *            the i2c address the device can be found on. Defaults to 0x5A.
 *  @param    touchThreshold
 *            touch detection threshold value
 *  @param    releaseThreshold
 *            release detection threshold value
 *  @param    autoconfig
 *            enable autoconfig option
 *  @returns  true on success, false otherwise
 */
MPR121::MPR121(uint8_t _port, uint8_t i2c_addr) {
    port = _port;
    addr = i2c_addr;
}

void MPR121::init(uint8_t touchThreshold, uint8_t releaseThreshold, bool autoconfig) {
    writeRegister(MPR121_SOFTRESET, 0x63);

    sleep_ms(1);

    // for (uint8_t i = 0; i < 0x7F; i++) {
    //     //  Serial.print("$"); Serial.print(i, HEX);
    //     //  Serial.print(": 0x"); Serial.println(readRegister8(i), HEX);
    // }

    writeRegister(MPR121_ECR, 0x0);

    uint8_t c = readRegister8(MPR121_CONFIG2);
#ifdef ENABLE_DEBUG
    // printf("read: MPR121_CONFIG2 = 0x%2x\n", c);
#endif
    if (c != 0x24) {
        DEBUG("mpr121 init failed!");
        good = false;
        return;
    }

    // Serial.println("write Configuration to sensor ...");
    setThresholds(touchThreshold, releaseThreshold);
    writeRegister(MPR121_MHDR, 0x01);
    writeRegister(MPR121_NHDR, 0x01);
    writeRegister(MPR121_NCLR, 0x0E);
    writeRegister(MPR121_FDLR, 0x00);

    writeRegister(MPR121_MHDF, 0x01);
    writeRegister(MPR121_NHDF, 0x05);
    writeRegister(MPR121_NCLF, 0x01);
    writeRegister(MPR121_FDLF, 0x00);

    writeRegister(MPR121_NHDT, 0x00);
    writeRegister(MPR121_NCLT, 0x00);
    writeRegister(MPR121_FDLT, 0x00);

    writeRegister(MPR121_DEBOUNCE, 0);
    writeRegister(MPR121_CONFIG1, 0x10);  // default, 16uA charge current
    writeRegister(MPR121_CONFIG2, 0x20);  // 0.5uS encoding, 1ms period

    setAutoconfig(autoconfig);

    // enable X electrodes = start MPR121
    // CL Calibration Lock: B10 = 5 bits for baseline tracking
    // ELEPROX_EN  proximity: disabled
    // ELE_EN Electrode Enable:  amount of electrodes running (12)
    uint8_t ECR_SETTING = 0b10000000 + 12;
    writeRegister(MPR121_ECR, ECR_SETTING);  // start with above ECR setting
    good = true;
}

/*!
 *  @brief      returns true if this mpr121 is ready.
 */
bool MPR121::ready() {
    return good;
}

/*!
 *  @brief      Enable autoconfig option.
 *  @param      autoconfig
 *              enable / disabled autoconfig
 *              when enabled, the MPR121 automatically searches and sets the
 *              charging parameters for every enabled pad.
 *              this happens on each time the MPR121 transitions
 *              from Stop Mode to Run Mode.
 */
void MPR121::setAutoconfig(bool autoconfig) {
    // register map at
    // https://www.nxp.com/docs/en/data-sheet/MPR121.pdf#page=17&zoom=auto,-416,747
    if (autoconfig) {
        // recommend settings found at
        // https://www.nxp.com/docs/en/application-note/AN3889.pdf#page=9&zoom=310,-42,373
        // FFI (First Filter Iterations) same as FFI in CONFIG1
        // FFI           → 00 Sets samples taken to 6 (Default)
        // RETRY
        // RETRY
        // BVA same as CL in ECR
        // BVA same as CL in ECR
        // ARE Auto-Reconfiguration Enable
        // ACE Auto-Configuration Enable
        // 0x0B == 0b00001011
        writeRegister(MPR121_AUTOCONFIG0, 0b00001011);

        // details on values
        // https://www.nxp.com/docs/en/application-note/AN3889.pdf#page=7&zoom=310,-42,792
        // correct values for Vdd = 3.3V
        writeRegister(MPR121_UPLIMIT, 200);      // ((Vdd - 0.7)/Vdd) * 256
        writeRegister(MPR121_TARGETLIMIT, 180);  // UPLIMIT * 0.9
        writeRegister(MPR121_LOWLIMIT, 130);     // UPLIMIT * 0.65
    } else {
        // really only disable ACE.
        writeRegister(MPR121_AUTOCONFIG0, 0b00001010);
    }
}

/*!
 *  @brief      Set the touch and release thresholds for all 13 channels on the
 *              device to the passed values. The threshold is defined as a
 *              deviation value from the baseline value, so it remains constant
 * even baseline value changes. Typically the touch threshold is a little bigger
 * than the release threshold to touch debounce and hysteresis. For typical
 * touch application, the value can be in range 0x05~0x30 for example. The
 * setting of the threshold is depended on the actual application. For the
 * operation details and how to set the threshold refer to application note
 * AN3892 and MPR121 design guidelines.
 *  @param      touch
 *              the touch threshold value from 0 to 255.
 *  @param      release
 *              the release threshold from 0 to 255.
 */
void MPR121::setThresholds(uint8_t touch, uint8_t release) {
    // set all thresholds (the same)
    for (uint8_t i = 0; i < 12; i++) {
        writeRegister(MPR121_TOUCHTH_0 + 2 * i, touch);
        writeRegister(MPR121_RELEASETH_0 + 2 * i, release);
    }
}

// /*!
//  *  @brief      Set the touch and release thresholds for each channels on the
//  *              device to the passed values.
//  *  @param      touch
//  *              the touch threshold collection.
//  *  @param      release
//  *              the release threshold collection.
//  */
// void MPR121::setThresholds(mpr121Thresholds* Thresholds) {
//     for (int i = 0; i < 12; i++) {
//         writeRegister(MPR121_TOUCHTH_0 + 2 * i, Thresholds->touch[i]);
//         writeRegister(MPR121_RELEASETH_0 + 2 * i, Thresholds->release[i]);
//     }
// }

/*!
 *  @brief      Set the touch and release debounce value for every channel.
 *  @param      dt
 *              touch.
 *  @param      dr
 *              release.
 */
void MPR121::setDebounce(uint8_t dt, uint8_t dr) {
    dt &= 0b111;
    dr &= 0b111;
    uint8_t debounce = dt | (dr << 4);
    writeRegister(MPR121_DEBOUNCE, debounce);
}

/*!
 *  @brief      Read the filtered data from channel t. The ADC raw data outputs
 *              run through 3 levels of digital filtering to filter out the high
 * frequency and low frequency noise encountered. For detailed information on
 * this filtering see page 6 of the device datasheet.
 *  @param      t
 *              the channel to read
 *  @returns    the filtered reading as a 10 bit unsigned value
 */
uint16_t MPR121::filteredData(uint8_t t) {
    if (t > 12)
        return 0;
    return readRegister16(MPR121_FILTDATA_0L + t * 2);
}

/*!
 *  @brief      Read the baseline value for the channel. The 3rd level filtered
 *              result is internally 10bit but only high 8 bits are readable
 * from registers 0x1E~0x2A as the baseline value output for each channel.
 *  @param      t
 *              the channel to read.
 *  @returns    the baseline data that was read
 */
uint16_t MPR121::baselineData(uint8_t t) {
    if (t > 12)
        return 0;
    uint16_t bl = readRegister8(MPR121_BASELINE_0 + t);
    return (bl << 2);
}

/**
 *  @brief      Read the touch status of all 13 channels as bit values in a 12
 * bit integer.
 *  @returns    a 12 bit integer with each bit corresponding to the touch status
 *              of a sensor. For example, if bit 0 is set then channel 0 of the
 * device is currently deemed to be touched.
 */
uint16_t MPR121::touched(void) {
    uint16_t t = readRegister16(MPR121_TOUCHSTATUS_L);
    return t & 0x0FFF;
}

/*!
 *  @brief      Read the contents of an 8 bit device register.
 *  @param      reg the register address to read from
 *  @returns    the 8 bit value that was read.
 */
uint8_t MPR121::readRegister8(uint8_t reg) {
    uint8_t buffer[1];
    i2c_write(port, addr, &reg, 1, true);  // 写入要读取的地址
    i2c_read(port, addr, buffer, 1, false);
    return buffer[0];
}

/*!
 *  @brief      Read the contents of a 16 bit device register.
 *  @param      reg the register address to read from
 *  @returns    the 16 bit value that was read.
 */
uint16_t MPR121::readRegister16(uint8_t reg) {
    uint8_t buffer[2];
    i2c_write(port, addr, &reg, 1, true);  // 写入要读取的地址
    i2c_read(port, addr, buffer, 2, false);
    // 实际先发送低位再发送高位
    // 原始数据 0x0102 = [0]0b00000001 [1]00000010
    // 接受 [0]00000010 [1]10000000
    // 因为是先读低字节再读高字节
    // 需要翻转
    uint16_t val = buffer[1];
    val <<= 8;
    val |= buffer[0];
    return val;
}

/*!
    @brief  Writes 8-bits to the specified destination register
    @param  reg the register address to write to
    @param  value the value to write
*/
void MPR121::writeRegister(uint8_t reg, uint8_t value) {
    // MPR121 must be put in Stop Mode to write to most registers
    bool stop_required = true;

    // first get the current set value of the MPR121_ECR register
    // Adafruit_BusIO_Register ecr_reg = Adafruit_BusIO_Register(i2c_dev, MPR121_ECR, 1);

    // uint8_t ecr_backup = ecr_reg.read();

    uint8_t ecr_backup = readRegister8(MPR121_ECR);

    if ((reg == MPR121_ECR) || ((0x73 <= reg) && (reg <= 0x7A))) {
        stop_required = false;
    }

    uint8_t data[2] = { 0x00, 0x00 };

    if (stop_required) {
        // clear this register to set stop mode
        // ecr_reg.write(0x00);
        data[0] = MPR121_ECR;
        data[1] = 0x00;
        i2c_write(port, addr, data, 2, false);
    }

    // Adafruit_BusIO_Register the_reg = Adafruit_BusIO_Register(i2c_dev, reg, 1);
    // the_reg.write(value);
    data[0] = reg;
    data[1] = value;
    i2c_write(port, addr, data, 2, false);

    if (stop_required) {
        // write back the previous set ECR settings
        // ecr_reg.write(ecr_backup);
        data[0] = MPR121_ECR;
        data[1] = ecr_backup;
        i2c_write(port, addr, data, 2, false);
    }
}
