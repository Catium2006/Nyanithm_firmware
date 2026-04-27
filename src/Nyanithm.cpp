
#include "pico/stdlib.h"
#include <stdio.h>

#define __NYANITHM_CPP__

#include <boot_mode.h>
#include <usb_device.h>


int main() {

    sleep_ms(10);
    initUSBDevice();
         

    sleep_ms(10);
    boot_switch();

}
