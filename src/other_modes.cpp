#include <controller_config.h>
#include <hw_devices.h>
#include <tusb.h>
#include <usb_device.h>
#include <chuni_io.h>

void start_4kMode() {

    while (true) {

        updateInputState();
        updateTouchData4k();
        maindev_loop();
        led_controller.fill(WS2812::RGB(0x08, 0x08, 0x08));
        led_controller.setPixelColor(7, WS2812::RGB(ControllerConfig.lightLimit, 0, ControllerConfig.lightLimit));
        led_controller.setPixelColor(15, WS2812::RGB(ControllerConfig.lightLimit, 0, ControllerConfig.lightLimit));
        led_controller.setPixelColor(23, WS2812::RGB(ControllerConfig.lightLimit, 0, ControllerConfig.lightLimit));

        // K
        if (touchData4k[0]) {
            for (int j = 0; j < 7; j++)
                led_controller.setPixelColor(30 - j, WS2812::RGB(ControllerConfig.lightLimit, ControllerConfig.lightLimit, 0));
        }
        // J
        if (touchData4k[1]) {
            for (int j = 0; j < 7; j++)
                led_controller.setPixelColor(22 - j, WS2812::RGB(ControllerConfig.lightLimit, ControllerConfig.lightLimit, 0));
        }
        // F
        if (touchData4k[2]) {
            for (int j = 0; j < 7; j++)
                led_controller.setPixelColor(14 - j, WS2812::RGB(ControllerConfig.lightLimit, ControllerConfig.lightLimit, 0));
        }
        // D
        if (touchData4k[3]) {
            for (int j = 0; j < 7; j++)
                led_controller.setPixelColor(6 - j, WS2812::RGB(ControllerConfig.lightLimit, ControllerConfig.lightLimit, 0));
        }

        led_controller.show();

        /*------------- Keyboard -------------*/
        if (tud_hid_n_ready(0)) {
            /**
             * report_buf
             * [0]
             * [1]
             * [2] A - H
             * [3] I - P
             * [4] Q - X
             * [5] Y, Z, 1 - 6
             * [6] 7 - 0, ENTER, ESCAPE, DELETE, TAB
             * [7] SPACE, -_, =+, [{, ]}, \|, [?], [?]
             */
            uint8_t report_buf[15];
            memset(report_buf, 0x00, sizeof(report_buf));

            // K
            if (touchData4k[0]) {
                report_buf[3] |= 0b00000100;
            }
            // J
            if (touchData4k[1]) {
                report_buf[3] |= 0b00000010;
            }
            // F
            if (touchData4k[2]) {
                report_buf[2] |= 0b00100000;
            }
            // D
            if (touchData4k[3]) {
                report_buf[2] |= 0b00001000;
            }

            // if (getButtonState(BUTTON_UP)) {
            //     report_buf[6] |= 0b00010000;  // ENTER
            // } else if (getButtonState(BUTTON_DOWN)) {
            //     report_buf[8] |= 0b10000000;  // F2
            // } else if (getButtonState(BUTTON_PUSH)) {
            //     report_buf[6] |= 0b00100000;  // ESCAPE
            // }
            tud_hid_n_report(0, 0, report_buf, sizeof(report_buf));
        }
    }
}

void start_6kMode() {
    while (true) {
        updateInputState();
        updateTouchData6k();
        maindev_loop();
        led_controller.fill(WS2812::RGB(0, 0, 0));

        led_controller.setPixelColor(2, WS2812::RGB(25, 0, 0));
        led_controller.setPixelColor(3, WS2812::RGB(25, 0, 0));
        led_controller.setPixelColor(4, WS2812::RGB(25, 0, 0));

        led_controller.setPixelColor(6, WS2812::RGB(0, 25, 0));
        led_controller.setPixelColor(7, WS2812::RGB(0, 25, 0));
        led_controller.setPixelColor(8, WS2812::RGB(0, 25, 0));

        led_controller.setPixelColor(10, WS2812::RGB(0, 0, 25));
        led_controller.setPixelColor(11, WS2812::RGB(0, 0, 25));
        led_controller.setPixelColor(12, WS2812::RGB(0, 0, 25));

        led_controller.setPixelColor(18, WS2812::RGB(25, 0, 0));
        led_controller.setPixelColor(19, WS2812::RGB(25, 0, 0));
        led_controller.setPixelColor(20, WS2812::RGB(25, 0, 0));

        led_controller.setPixelColor(22, WS2812::RGB(0, 25, 0));
        led_controller.setPixelColor(23, WS2812::RGB(0, 25, 0));
        led_controller.setPixelColor(24, WS2812::RGB(0, 25, 0));

        led_controller.setPixelColor(26, WS2812::RGB(0, 0, 25));
        led_controller.setPixelColor(27, WS2812::RGB(0, 0, 25));
        led_controller.setPixelColor(28, WS2812::RGB(0, 0, 25));

        if (touchData6k[0]) {
            led_controller.setPixelColor(2, WS2812::RGB(ControllerConfig.lightLimit, 0, 0));
            led_controller.setPixelColor(3, WS2812::RGB(ControllerConfig.lightLimit, 0, 0));
            led_controller.setPixelColor(4, WS2812::RGB(ControllerConfig.lightLimit, 0, 0));
        }
        if (touchData6k[1]) {
            led_controller.setPixelColor(6, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
            led_controller.setPixelColor(7, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
            led_controller.setPixelColor(8, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
        }
        if (touchData6k[2]) {
            led_controller.setPixelColor(10, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
            led_controller.setPixelColor(11, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
            led_controller.setPixelColor(12, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
        }
        if (touchData6k[3]) {
            led_controller.setPixelColor(18, WS2812::RGB(ControllerConfig.lightLimit, 0, 0));
            led_controller.setPixelColor(19, WS2812::RGB(ControllerConfig.lightLimit, 0, 0));
            led_controller.setPixelColor(20, WS2812::RGB(ControllerConfig.lightLimit, 0, 0));
        }
        if (touchData6k[4]) {
            led_controller.setPixelColor(22, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
            led_controller.setPixelColor(23, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
            led_controller.setPixelColor(24, WS2812::RGB(0, ControllerConfig.lightLimit, 0));
        }
        if (touchData6k[5]) {
            led_controller.setPixelColor(26, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
            led_controller.setPixelColor(27, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
            led_controller.setPixelColor(28, WS2812::RGB(0, 0, ControllerConfig.lightLimit));
        }
        led_controller.show();

        /*------------- Keyboard -------------*/
        if (tud_hid_n_ready(0)) {
            /**
             * report_buf
             * [0]
             * [1]
             * [2] A - H
             * [3] I - P
             * [4] Q - X
             * [5] Y, Z, 1 - 6
             * [6] 7 - 0, ENTER, ESCAPE, DELETE, TAB
             * [7] SPACE, -_, =+, [{, ]}, \|, [?], [?]
             */
            uint8_t report_buf[15];
            memset(report_buf, 0x00, sizeof(report_buf));

            // L
            if (touchData6k[5]) {
                report_buf[3] |= 0b00001000;
            }
            // K
            if (touchData6k[4]) {
                report_buf[3] |= 0b00000100;
            }
            // J
            if (touchData6k[3]) {
                report_buf[3] |= 0b00000010;
            }
            // D
            if (touchData6k[2]) {
                report_buf[2] |= 0b00001000;
            }
            // S
            if (touchData6k[1]) {
                report_buf[4] |= 0b00000100;
            }
            // A
            if (touchData6k[0]) {
                report_buf[2] |= 0b00000001;
            }

            // if (getButtonState(BUTTON_UP)) {
            //     report_buf[6] |= 0b00010000;  // ENTER
            // } else if (getButtonState(BUTTON_DOWN)) {
            //     report_buf[8] |= 0b10000000;  // F2
            // } else if (getButtonState(BUTTON_PUSH)) {
            //     report_buf[6] |= 0b00100000;  // ESCAPE
            // }

            tud_hid_n_report(0, 0, report_buf, sizeof(report_buf));
        }
    }
}