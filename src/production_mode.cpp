
#include <cy8cmbr3116.h>
#include <cy8cmbr3116_cfg.h>

#include <production_mode.h>
#include <stdio.h>

bool detect3116(uint8_t addr) {
    // 尝试读取地址寄存器值
    uint8_t buf[1] = { I2C_ADDR_ADDRESS };
    i2c_write(0, addr, buf, 1, true);
    buf[0] = 0;
    i2c_read(0, addr, buf, 1, true);
    if (buf[0] == addr) {
        return true;
    }
    return false;
}

void program_cy8cmbr3116_custom(uint8_t addr, uint8_t* cfg) {
    for (uint8_t i = 0; i < 128; i++) {
        uint8_t buf[2] = { i, cfg[i] };
        i2c_write(0, addr, buf, 2, true);
    }
    uint8_t buf[2] = { CTRL_CMD_ADDRESS, 0x02 };  // 给CTRL_CMD发送命令，检查CRC并保存，地址0x86，写入2
    i2c_write(0, addr, buf, 2, true);
    sleep_ms(10);

    buf[1] = 0x02;  // 应用设置
    i2c_write(0, addr, buf, 2, true);

    buf[1] = 0xff;  // 软复位
    i2c_write(0, addr, buf, 2, true);
    sleep_ms(10);
}

void program3116() {
    while (1) {
        printf("\n");
        if (detect3116(0x43) && detect3116(0x44)) {
            printf("+-----------------------------+\n");
            printf("|both 0x43 and 0x44 are ready.|\n");
            printf("+-----------------------------+\n");
        } else if (detect3116(0x43)) {
            if (detect3116(0x37)) {
                printf("programing 0x44.\n");
                program_cy8cmbr3116_custom(0x37, cy8cmbr3116_cfg_0x44);
            } else {
                printf("waiting for the SECOND chip.\n");
            }
        } else if (detect3116(0x37)) {
            printf("programing 0x43.\n");
            program_cy8cmbr3116_custom(0x37, cy8cmbr3116_cfg_0x43);
        } else {
                printf("waiting for the FIRST chip.\n");
        }
        sleep_ms(500);
    }
}

void productionMode() {
    program3116();
}