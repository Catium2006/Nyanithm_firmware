#include <controller_config.h>
#include <error_state.h>
#include <gpio_def.h>
#include <hw_check.h>
#include <i2c_port.h>
#include <pca954x.h>

void checkToF() {
    if (!findI2CDevice(1, 0x70)) {
        error(true);
    }
    PCA954X mux(1, 0x70, GPIO_PCA9545_RESET);

    mux.setChannel(0);
    if (!findI2CDevice(1, 0x29)) {
        warn(true);
    }
    mux.setChannel(1);
    if (!findI2CDevice(1, 0x29)) {
        warn(true);
    }
    mux.setChannel(2);
    if (!findI2CDevice(1, 0x29)) {
        warn(true);
    }
    mux.setChannel(3);
    if (!findI2CDevice(1, 0x29)) {
        warn(true);
    }

    // if (ControllerConfig.hwVer == 2) {
    //     mux.setChannel(4);
    //     if (!findI2CDevice(1, 0x29)) {
    //         warn(true);
    //     }
    // }

    mux.setReg(0x00);
}

void check3116() {
    // if (!findI2CDevice(0, 0x40)) {
    //     warn(true);
    // }a
    // if (!findI2CDevice(0, 0x41)) {
    //     warn(true);
    // }
    // if (!findI2CDevice(0, 0x42)) {
    //     warn(true);
    // }
}

void checkMPR121() {
    if (!findI2CDevice(0, 0x5a)) {
        warn(true);
    }
    if (!findI2CDevice(0, 0x5b)) {
        warn(true);
    }
    if (!findI2CDevice(0, 0x5c)) {
        warn(true);
    }
}

void chekcHardwareState() {

    // if (ControllerConfig.cfg0 & CFG0_BIT_MBR3116) {
    //     check3116();
    // } else {
    //     checkMPR121();
    // }
    // checkToF();
}