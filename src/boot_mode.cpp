
#include <app_link.h>
#include <boot_mode.h>
#include <button.h>
#include <chuni_io.h>
#include <controller_config.h>
#include <gpio_def.h>
#include <hardware/flash.h>
#include <hardware/watchdog.h>
#include <hw_check.h>
#include <hw_devices.h>
#include <i2c_port.h>
#include <pico/flash.h>
#include <production_mode.h>
#include <rainbow.h>

void reboot() {
    watchdog_reboot(0, 0, 10);
}

void boot_switch() {
    initButtons();
    sleep_ms(10);

    if (getButtonState(BUTTON_PUSH)) {
        boot_appLinkMode();
    } else if (getButtonState(BUTTON_UP)) {
        boot_productionMode();
        // boot_flashing();
    } else if (getButtonState(BUTTON_DOWN)) {
        boot_otherModes();
    } else {
        boot_normalMode();
    }
}

void boot_productionMode() {
    hid_working = false;
    game_connected = true;
    initI2CBus(0, GPIO_I2C_0_SDA, GPIO_I2C_0_SCL, BR200K);
    RGB_LED.fill(WS2812::RGB(0xff, 0xff, 0xff));
    RGB_LED.show();

    productionMode();

}

void boot_appLinkMode() {
    RGB_LED.fill(WS2812::RGB(0x00, 0x0f, 0x00));
    RGB_LED.show();

    hid_working = false;

    sleep_ms(10);
    readConfig();
    initHwDevices();
    sleep_ms(10);
    handleCommand();

    reboot();
}

void boot_normalMode() {
    RGB_LED.fill(WS2812::RGB(0x0f, 0x0f, 0x0f));
    RGB_LED.show();

    sleep_ms(10);
    readConfig();

    sleep_ms(10);
    initHwDevices();

    sleep_ms(10);
    chekcHardwareState();

    sleep_ms(10);
    while (true) {
        // if (!game_connected) {
        //     // update_rainbow_frame();
        // }
        updateInputState();
        maindev_loop();
    }
}

void start_4kMode();
void start_6kMode();

void boot_otherModes() {
    readConfig();

    sleep_ms(10);
    initHwDevices();

    sleep_ms(10);
    chekcHardwareState();

    sleep_ms(10);
    hid_working = false;
    RGB_LED.fill(WS2812::RGB(0, 0, 0));
    for (int j = 0; j < 7; j++)
        RGB_LED.setPixelColor(30 - j, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
    for (int j = 0; j < 7; j++)
        RGB_LED.setPixelColor(22 - j, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
    // // F
    //     for (int j = 0; j < 7; j++)
    //         RGB_LED.setPixelColor(14 - j, WS2812::RGB(255, 255, 0));
    // // D
    //     for (int j = 0; j < 7; j++)
    //         RGB_LED.setPixelColor(6 - j, WS2812::RGB(255, 255, 0));

    RGB_LED.show();
    while (true) {
        updateInputState();
        updateTouchData4k();
        if (touchData4k[0]) {
            start_4kMode();
        }
        if (touchData4k[1]) {
            start_6kMode();
        }
    }
}

void boot_flashing() {
    flash_safe_execute([](void* p) { flash_range_erase(0, 4096); }, nullptr, 100);
    reboot();
}