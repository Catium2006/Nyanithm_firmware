/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <ctype.h>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp/board_api.h"
#include "tusb.h"

#include <pico/flash.h>
#include <pico/multicore.h>
#include <pico/stdio/driver.h>

#include <serial_io.h>
#include <controller_config.h>
#include <hw_devices.h>
#include <lamp_array.h>
#include <usb_device.h>

void multicore_entry() {
    // multicore_lockout_victim_init();  // 初始化当前内核（内核1），使其可以被内核0中断
    flash_safe_execute_core_init();  // 初始化当前内核（内核1），使其可以被内核0中断

    while (true) {
        tud_task();
        hid_task_chuni_input();
        sleep_us(500);
    }
}

void stdio_init_cdc();

/*------------- MAIN -------------*/
void initUSBDevice(void) {
    board_init();

    // init device stack on configured roothub port
    tusb_rhport_init_t dev_init = { .role = TUSB_ROLE_DEVICE, .speed = TUSB_SPEED_AUTO };
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    stdio_init_cdc();
    lamp_array_init();

    if (board_init_after_tusb) {
        board_init_after_tusb();
    }

    multicore_launch_core1(multicore_entry);
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    if (itf == HID_INSTANCE_LAMP_ARRAY) {
        return lamp_array_get_report(report_id, report_type, buffer, reqlen);
    }
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    if (itf == HID_INSTANCE_LAMP_ARRAY) {
        lamp_array_set_report(report_id, report_type, buffer, bufsize);
    }
}

// PICO_CONFIG: PICO_STDIO_USB_STDOUT_TIMEOUT_US, Number of microseconds to be blocked trying to write USB output before assuming the host has disappeared and discarding data, default=500000,
// group=pico_stdio_usb
#ifndef PICO_STDIO_USB_STDOUT_TIMEOUT_US
#define PICO_STDIO_USB_STDOUT_TIMEOUT_US 500000
#endif

static mutex_t stdio_usb_mutex;

static void stdio_cdc_out_chars(const char* buf, int length) {
    static uint64_t last_avail_time;
    if (!mutex_try_enter_block_until(&stdio_usb_mutex, make_timeout_time_ms(PICO_STDIO_DEADLOCK_TIMEOUT_MS))) {
        return;
    }
    if (tud_ready()) {
        for (int i = 0; i < length;) {
            int n = length - i;
            int avail = (int)tud_cdc_write_available();
            if (n > avail)
                n = avail;
            if (n) {
                int n2 = (int)tud_cdc_write(buf + i, (uint32_t)n);
                tud_task();
                tud_cdc_write_flush();
                i += n2;
                last_avail_time = time_us_64();
            } else {
                tud_task();
                tud_cdc_write_flush();
                if (!tud_ready() || (!tud_cdc_write_available() && time_us_64() > last_avail_time + PICO_STDIO_USB_STDOUT_TIMEOUT_US)) {
                    break;
                }
            }
        }
    } else {
        // reset our timeout
        last_avail_time = 0;
    }
    mutex_exit(&stdio_usb_mutex);
}

static void stdio_cdc_out_flush(void) {
    if (!mutex_try_enter_block_until(&stdio_usb_mutex, make_timeout_time_ms(PICO_STDIO_DEADLOCK_TIMEOUT_MS))) {
        return;
    }
    do {
        tud_task();
    } while (tud_cdc_write_flush());
    mutex_exit(&stdio_usb_mutex);
}

int stdio_cdc_in_chars(char* buf, int length) {
    // note we perform this check outside the lock, to try and prevent possible deadlock conditions
    // with printf in IRQs (which we will escape through timeouts elsewhere, but that would be less graceful).
    //
    // these are just checks of state, so we can call them while not holding the lock.
    // they may be wrong, but only if we are in the middle of a tud_task call, in which case at worst
    // we will mistakenly think we have data available when we do not (we will check again), or
    // tud_task will complete running and we will check the right values the next time.
    //
    int rc = PICO_ERROR_NO_DATA;
    if (tud_ready() && tud_cdc_available()) {
        if (!mutex_try_enter_block_until(&stdio_usb_mutex, make_timeout_time_ms(PICO_STDIO_DEADLOCK_TIMEOUT_MS))) {
            return PICO_ERROR_NO_DATA;  // would deadlock otherwise
        }
        if (tud_ready() && tud_cdc_available()) {
            int count = (int)tud_cdc_read(buf, (uint32_t)length);
            rc = count ? count : PICO_ERROR_NO_DATA;
        } else {
            // because our mutex use may starve out the background task, run tud_task here (we own the mutex)
            tud_task();
        }
        mutex_exit(&stdio_usb_mutex);
    }
    return rc;
}

stdio_driver_t stdio_cdc = { .out_chars = stdio_cdc_out_chars, .out_flush = stdio_cdc_out_flush, .in_chars = stdio_cdc_in_chars, .last_ended_with_cr = false, .crlf_enabled = false };

void stdio_init_cdc() {
    if (!mutex_is_initialized(&stdio_usb_mutex))
        mutex_init(&stdio_usb_mutex);
    stdio_set_driver_enabled(&stdio_cdc, true);
}
