#include <boot_mode.h>
#include <chuni_io.h>
#include <controller_config.h>
#include <gpio_def.h>
#include <hw_devices.h>
#include <nyanithm_shared.h>
#include <tusb.h>

bool hid_working;

// called by usb_device.cpp to run in core #1, while main codes run in core #0
void hid_task_chuni_input() {
    if(!hid_working) {
        return;
    }

    // Poll every 2ms
    const uint32_t interval_ms = 2;
    static uint32_t start_ms = 0;

    if(to_ms_since_boot(get_absolute_time()) - start_ms < interval_ms)
        return; // not enough time
    start_ms += interval_ms;

    // Remote wakeup
    if(tud_suspended()) {
        tud_remote_wakeup();
    }

    /*------------- Keyboard -------------*/
    if(tud_hid_n_ready(0)) {
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

        // touch
        if(ControllerConfig.cfg1 & CFG1_BIT_ENABLE_SLIDER_INPUT_AS_KEYBOARD) {
            report_buf[2] = touchData[0];
            report_buf[3] = touchData[1];
            report_buf[4] = touchData[2];
            report_buf[5] = touchData[3];
        }

        // air
        if(ControllerConfig.cfg1 & CFG1_BIT_ENABLE_AIR_INPUT_AS_KEYBOARD) {
            for(int i = 0; i < 6; i++) {
                if(airKeys[i]) {
                    report_buf[9] |= (1 << i);
                }
            }
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

#define CLAMP(val, lo, hi) (val < lo ? lo : (val > hi ? hi : val))

extern uint8_t touchData32[32];

bool game_connected;
uint32_t connected_time;

struct NyanithmInput {
    uint8_t slider[32];
    uint8_t air;
};

NyanithmInput inputState;

uint8_t inputState_buffer[16][32];

void syncInputState() {
    uint8_t ltc = ControllerConfig.latency;
    if(ltc > 15) {
        ltc = 15;
    }
    for(int i = 0; i < 32; i++) {
        inputState_buffer[0][i] = touchData32[i];
    }
    for(int i = ltc; i > 0; i--) {
        for(int j = 0; j < 32; j++) {
            inputState_buffer[i][j] = inputState_buffer[i - 1][j];
        }
    }
    for(int i = 0; i < 32; i++) {
        inputState.slider[i] = inputState_buffer[ltc][i];
    }
    inputState.air = 0;
    for(int i = 0; i < 6; i++) {
        if(airKeys[i]) {
            inputState.air |= 1 << i;
        }
    }
}

void maindev_loop() {

    syncInputState();

    while(tud_cdc_available()) {
        game_connected = true;
        connected_time = to_ms_since_boot(get_absolute_time());
        uint8_t cmd = getchar();
        if(cmd == CMD_GET_API_LEVEL) {
            putchar(NYANITHM_API_LEVEL);
        } else if(cmd == CMD_DEV_DETECT) {
            putchar(CMD_DEV_DETECT);
        } else if(cmd == CMD_GET_INPUT) {
            uint8_t* ptr = (uint8_t*)&inputState;
            for(int i = 0; i < sizeof(NyanithmInput); i++) {
                putchar(*ptr);
                ptr++;
            }
        } else if(cmd == CMD_SET_LED) {
            uint8_t leds[96];
            for(int i = 0; i < 96; i++) {
                leds[i] = getchar();
            }
            uint8_t r, g, b;
            for(int i = 0; i < 31; i++) {
                b = leds[i * 3 + 0];
                r = leds[i * 3 + 1];
                g = leds[i * 3 + 2];
                uint32_t R = (r * ControllerConfig.lightLimit) / 255;
                uint32_t G = (g * ControllerConfig.lightLimit) / 255;
                uint32_t B = (b * ControllerConfig.lightLimit) / 255;
                r = R;
                g = G;
                b = B;
                // 降低间隙亮度
                if((i & 1) && (ControllerConfig.cfg0 & CFG0_BIT_DARKER_GAP)) {
                    r >>= 2;
                    g >>= 2;
                    b >>= 2;
                }
                led_controller.setColor(30 - i, r, g, b);
            }
            led_controller.flush();
        } else if(cmd == CMD_FLASHING) {
            boot_flashing();
        } else if(cmd == CMD_CFG_ERASE) {
            eraseConfigSector();
        } else if(cmd == CMD_CFG_READ) {
            readConfig();
            uint8_t* ptr = (uint8_t*)&ControllerConfig;
            for(int i = 0; i < sizeof(controller_config); i++) {
                putchar(*ptr);
                ptr++;
            }
        } else if(cmd == CMD_CFG_SET) {
            setConfig();
        } else if(cmd == CMD_CFG_SAVE) {
            saveConfig();
        } else if(cmd == CMD_LOAD3116CONFIG) {
            uint8_t address = getchar();
            uint8_t cfg[128];
            for(int i = 0; i < 128; i++) {
                cfg[i] = getchar();
            }
            program_cy8cmbr3116_custom(address, cfg);
        }
    }
    if(to_ms_since_boot(get_absolute_time()) - connected_time > 2000) {
        game_connected = false;
    }
}
