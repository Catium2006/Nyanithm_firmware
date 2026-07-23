/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */


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
