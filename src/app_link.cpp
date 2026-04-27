#include <app_link.h>
#include <button.h>
#include <production_mode.h>
#include <boot_mode.h>
#include <controller_config.h>
#include <hw_devices.h>
#include <nyanithm_shared.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <tusb.h>

bool hid_working = true;

void getStatus() {
    printf("Nyanithm build " __DATE__ " " __TIME__ "\n");
    printf("hwVer: %d\n", ControllerConfig.hwVer);
    if (ControllerConfig.hwVer == 1 || ControllerConfig.hwVer == 3) {
        printf("original ToF distance (or error code):\n    tof0 = %d tof1 = %d tof2 = %d  tof3 = %d\n", heightDataOriginal[0], heightDataOriginal[1], heightDataOriginal[2], heightDataOriginal[3]);
        printf("using config in page %d\n", getConfigPage());
        for (int i = 0; i < 4; i++) {
            if (heightDataOriginal[i] > 3000 && heightDataOriginal[i] != 8190) {
                printf("*********************\n");
                printf("ToF sensor #%d warning!\n", i);
                printf("*********************\n");
            }
        }
    }
    if (ControllerConfig.hwVer == 2 || ControllerConfig.hwVer == 4) {
        printf("original ToF distance (or error code):\n    tof0 = %d tof1 = %d tof2 = %d  tof3 = %d tof4 = %d\n", heightDataOriginal[0], heightDataOriginal[1], heightDataOriginal[2],
               heightDataOriginal[3], heightDataOriginal[4]);
        printf("using config in page %d\n", getConfigPage());
        for (int i = 0; i < 5; i++) {
            if (heightDataOriginal[i] > 3000 && heightDataOriginal[i] != 8190) {
                printf("*********************\n");
                printf("ToF sensor #%d warning!\n", i);
                printf("*********************\n");
            }
        }
    }
}


void handleCommand() {
    while (true) {
        while (tud_cdc_available() == 0) {
            sleep_ms(1);
            updateInputState();
        }
        uint8_t cmd = getchar();
        if (cmd == CMD_DEV_DETECT) {
            putchar(CMD_DEV_DETECT);
        } else if (cmd == CMD_CFG_READ) {
            readConfig();
            uint8_t* ptr = (uint8_t*)&ControllerConfig;
            for (int i = 0; i < sizeof(controller_config); i++) {
                putchar(*ptr);
                ptr++;
            }
            printf("read...\n");
            printf("using config in page %d\n", getConfigPage());
        } else if (cmd == CMD_CFG_ERASE) {
            printf("erase...\n");
            eraseConfigSector();
        } else if (cmd == CMD_CFG_SET) {
            // printf("set...");
            setConfig();
        } else if (cmd == CMD_CFG_SAVE) {
            printf("save...\n");
            saveConfig();
        } else if (cmd == CMD_GET_STATUS) {
            printf("get status...\n");
            getStatus();
        } else if (cmd == CMD_EXIT) {
            reboot();
        } else if (cmd == CMD_LOAD3116CONFIG) {
            uint8_t address = getchar();
            uint8_t cfg[128];
            for (int i = 0; i < 128; i++) {
                cfg[i] = getchar();
            }
            printf("programing 3116 chip\n");
            program_cy8cmbr3116_custom(address, cfg);
            printf("done\n");

        } else if (cmd == CMD_FLASHING) {
            boot_flashing();
        } else {
            printf("unknown command...\n");
        }
    }
}