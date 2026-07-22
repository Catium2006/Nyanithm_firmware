#include <boot_mode.h>
#include <chuni_io.h>
#include <controller_config.h>
#include <gpio_def.h>
#include <hardware/flash.h>
#include <hardware/watchdog.h>
#include <hw_devices.h>
#include <i2c_port.h>
#include <pico/bootrom.h>
#include <pico/flash.h>
#include <rainbow.h>

void reboot() {
    watchdog_reboot(0, 0, 10);
}

void boot_switch() {
    readConfig();
    sleep_ms(20);
    initHwDevices();
    sleep_ms(20);
    if(ControllerConfig.controller_mode == MODE_NORMAL) {
        boot_normalMode();
    } else if(ControllerConfig.controller_mode == MODE_4K) {
        start_4kMode();
    } else if(ControllerConfig.controller_mode == MODE_6K) {
        start_6kMode();
    } else {
        ControllerConfig.controller_mode = MODE_NORMAL;
        boot_normalMode();
    }
}

void boot_normalMode() {

    sleep_ms(10);
    hid_working = true;
    while(true) {
        if(!game_connected) {
            if(!(ControllerConfig.cfg0 & CFG0_BIT_ENABLE_LAMPARRAY)) {
                update_rainbow_frame();
            }
        }
        updateInputState();
        maindev_loop();
    }
}

void boot_flashing() {
    led_controller.fill(100, 0, 0);
    led_controller.flush();
    rom_reset_usb_boot(0, 0);
}