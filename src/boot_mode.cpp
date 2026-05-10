
#include <boot_mode.h>
#include <chuni_io.h>
#include <controller_config.h>
#include <gpio_def.h>
#include <hardware/flash.h>
#include <hardware/watchdog.h>
#include <hw_devices.h>
#include <i2c_port.h>
#include <pico/flash.h>
#include <rainbow.h>

void reboot() {
    watchdog_reboot(0, 0, 10);
}

void boot_switch() {
    readConfig();
    initHwDevices();
    sleep_ms(10);
    // if(ControllerConfig.controller_mode == MODE_NORMAL){
        boot_normalMode();
    // }

}

void boot_normalMode() {

    sleep_ms(10);
    while (true) {
        // if (!game_connected) {
        //     // update_rainbow_frame();
        // }
        updateInputState();
        maindev_loop();
    }
}

void boot_flashing() {
    flash_safe_execute([](void* p) { flash_range_erase(0, 4096); }, nullptr, 100);
    reboot();
}