#include <controller_config.h>
#include <hw_devices.h>
#include <tca9539.h>

VL53L0X tof0(1, 0x29);
VL53L0X tof1(1, 0x29);
VL53L0X tof2(1, 0x29);
VL53L0X tof3(1, 0x29);
VL53L0X tof4(1, 0x29);

CY8CMBR3116 MBR3116A(0, 0x40);
CY8CMBR3116 MBR3116B(0, 0x41);
CY8CMBR3116 MBR3116C(0, 0x42);

CY8CMBR3116 MBR3116D(0, 0x43);
CY8CMBR3116 MBR3116E(0, 0x44);

MPR121 mpr0(0, 0x5A);
MPR121 mpr1(0, 0x5B);
MPR121 mpr2(0, 0x5C);

PCA954X mux0(1, 0x70, GPIO_PCA9545_RESET);

WS2812 RGB_LED(GPIO_RGB, 31, pio0, 0, WS2812::FORMAT_GRB);

TCA9539 iox0(1, 0x74);

bool usingIR = false;

void initToFReset() {
    gpio_init(GPIO_TOF_RESET);
    gpio_set_dir(GPIO_TOF_RESET, true);
    gpio_pull_up(GPIO_TOF_RESET);
    gpio_put(GPIO_TOF_RESET, HIGH);
}

void resetToF() {
    gpio_put(GPIO_TOF_RESET, LOW);
    sleep_ms(1);
    gpio_put(GPIO_TOF_RESET, HIGH);
}

void initToF() {

    initToFReset();
    resetToF();

    sleep_ms(2);
    // printf("tof0\n");
    mux0.setChannel(0);
    tof0.setTimeout(0);
    // tof0.setAddress(0x50);
    tof0.forceInit();
    tof0.setMeasurementTimingBudget(20000);
    tof0.startContinuous(0);
    // printf("tof1\n");

    mux0.setChannel(1);
    tof1.setTimeout(0);
    // tof1.setAddress(0x51);
    tof1.forceInit();
    tof1.setMeasurementTimingBudget(20000);
    tof1.startContinuous(0);
    // printf("tof2\n");

    mux0.setChannel(2);
    tof2.setTimeout(0);
    // tof2.setAddress(0x52);
    tof2.forceInit();
    tof2.setMeasurementTimingBudget(20000);
    tof2.startContinuous(0);
    // printf("tof3\n");

    mux0.setChannel(3);
    tof3.setTimeout(0);
    // tof3.setAddress(0x53);
    tof3.forceInit();
    tof3.setMeasurementTimingBudget(20000);
    tof3.startContinuous(0);

    if (ControllerConfig.hwVer == 2 || ControllerConfig.hwVer == 4) {
        mux0.setChannel(4);
        tof4.setTimeout(0);
        // tof4.setAddress(0x54);
        tof4.forceInit();
        tof4.setMeasurementTimingBudget(30000);
        tof4.startContinuous(0);
    }

    // mux0.setReg(0x0f);
}

void initMPR121() {
    mpr0.init(4, 5, true);
    mpr1.init(4, 5, true);
    mpr2.init(4, 5, true);

    mpr0.setThresholds(ControllerConfig.th_touch, ControllerConfig.th_release);
    mpr1.setThresholds(ControllerConfig.th_touch, ControllerConfig.th_release);
    mpr2.setThresholds(ControllerConfig.th_touch, ControllerConfig.th_release);

    uint8_t dt, dr;
    dt = ControllerConfig.debounce & 0b0111;
    dr = (ControllerConfig.debounce >> 4) & 0b111;
    mpr0.setDebounce(dt, dr);
    mpr1.setDebounce(dt, dr);
    mpr2.setDebounce(dt, dr);
}

void initI2C() {
    initI2CBus(0, GPIO_I2C_0_SDA, GPIO_I2C_0_SCL, BR_I2C);
    initI2CBus(1, GPIO_I2C_1_SDA, GPIO_I2C_1_SCL, BR_I2C);
}

void program_cyc8mbr3116_with_address(uint8_t address, uint8_t* cfg) {
    for (uint8_t i = 0; i < 128; i++) {
        uint8_t buf[2] = { i, cfg[i] };
        i2c_write(0, address, buf, 2, false);
    }
    uint8_t buf[2] = { 0x86, 0x02 };  // 给CTRL_CMD发送命令，检查CRC并保存，地址0x86，写入2
    i2c_write(0, address, buf, 2, false);
    sleep_ms(20);

    buf[1] = 0xff;  // 软复位
    i2c_write(0, address, buf, 2, false);
    sleep_ms(20);
}

void initCY8CMBR3116() {
    // program_cyc8mbr3116_with_address(0x40, cy8cmbr3116_cfg_0x40);
    // program_cyc8mbr3116_with_address(0x41, cy8cmbr3116_cfg_0x41);
    // program_cyc8mbr3116_with_address(0x42, cy8cmbr3116_cfg_0x42);

    // gpio_init(GPIO_3116RST0);
    // gpio_init(GPIO_3116RST1);

    // gpio_set_dir(GPIO_3116RST0, true);
    // gpio_set_dir(GPIO_3116RST1, true);

    // gpio_pull_down(GPIO_3116RST0);
    // gpio_pull_down(GPIO_3116RST1);

    // gpio_set_drive_strength(GPIO_3116RST0,GPIO_DRIVE_STRENGTH_8MA);
    // gpio_set_drive_strength(GPIO_3116RST1,GPIO_DRIVE_STRENGTH_8MA);

    // gpio_put(GPIO_3116RST0, false);
    // sleep_ms(10);
    // gpio_put(GPIO_3116RST0, true);
    // gpio_put(GPIO_3116RST1, false);
    // sleep_ms(10);
    // gpio_put(GPIO_3116RST1, true);
}

void detectIR() {
    if (iox0.isConnected()) {
        usingIR = true;
    } else {
        usingIR = false;
    }
}

void initIR() {
    // 使用红外对射组件
    iox0.setConfP0(0x00);
    iox0.setConfP1(0xFF);
    // iox0.setOutputP0(0xFF);
}

void updateIR() {
    static int i = 0;
    // for (int i = 0; i < 6; i++) {
    uint8_t output_mask = 1 << i;
    iox0.setOutputP0(output_mask);
    sleep_us(100);
    uint8_t ir_state = iox0.getInputP1();
    airKeys[i] = ir_state & output_mask;
    // }
    i++;
    if (i == 6) {
        i = 0;
    }
}

void initHwDevices() {
    initI2C();
    detectIR();
    if (usingIR) {
        initIR();
    } else {
        mux0.init();
        initToF();
    }
    if (ControllerConfig.cfg0 & CFG0_BIT_MBR3116) {
        initCY8CMBR3116();
    } else {
        initMPR121();
    }
}

uint8_t touchData[4];
uint8_t touchData32[32];

#define GET_BIT(UNUM, BIT) (UNUM & (1 << BIT))

bool touchData4k[4];
bool touchData6k[6];

void updateTouch_v2() {
    uint16_t t0, t1;
    MBR3116D.get_BUTTON_STAT((uint8_t*)&t0);
    MBR3116E.get_BUTTON_STAT((uint8_t*)&t1);

    touchData[0] = *(0 + (uint8_t*)(&t0));
    touchData[1] = *(1 + (uint8_t*)(&t0));
    touchData[2] = *(0 + (uint8_t*)(&t1));
    touchData[3] = *(1 + (uint8_t*)(&t1));

    touchData32[0] = GET_BIT(t1, 4) ? 128 : 0;
    touchData32[1] = GET_BIT(t1, 0) ? 128 : 0;

    touchData32[2] = GET_BIT(t1, 5) ? 128 : 0;
    touchData32[3] = GET_BIT(t1, 1) ? 128 : 0;

    touchData32[4] = GET_BIT(t1, 6) ? 128 : 0;
    touchData32[5] = GET_BIT(t1, 2) ? 128 : 0;

    touchData32[6] = GET_BIT(t1, 7) ? 128 : 0;
    touchData32[7] = GET_BIT(t1, 3) ? 128 : 0;

    //

    touchData32[8] = GET_BIT(t1, 8) ? 128 : 0;
    touchData32[9] = GET_BIT(t1, 15) ? 128 : 0;

    touchData32[10] = GET_BIT(t1, 9) ? 128 : 0;
    touchData32[11] = GET_BIT(t1, 14) ? 128 : 0;

    touchData32[12] = GET_BIT(t1, 10) ? 128 : 0;
    touchData32[13] = GET_BIT(t1, 13) ? 128 : 0;

    touchData32[14] = GET_BIT(t1, 11) ? 128 : 0;
    touchData32[15] = GET_BIT(t1, 12) ? 128 : 0;

    //

    touchData32[16] = GET_BIT(t0, 12) ? 128 : 0;
    touchData32[17] = GET_BIT(t0, 11) ? 128 : 0;

    touchData32[18] = GET_BIT(t0, 13) ? 128 : 0;
    touchData32[19] = GET_BIT(t0, 10) ? 128 : 0;

    touchData32[20] = GET_BIT(t0, 14) ? 128 : 0;
    touchData32[21] = GET_BIT(t0, 9) ? 128 : 0;

    touchData32[22] = GET_BIT(t0, 15) ? 128 : 0;
    touchData32[23] = GET_BIT(t0, 8) ? 128 : 0;

    //

    touchData32[24] = GET_BIT(t0, 3) ? 128 : 0;
    touchData32[25] = GET_BIT(t0, 7) ? 128 : 0;

    touchData32[26] = GET_BIT(t0, 2) ? 128 : 0;
    touchData32[27] = GET_BIT(t0, 6) ? 128 : 0;

    touchData32[28] = GET_BIT(t0, 1) ? 128 : 0;
    touchData32[29] = GET_BIT(t0, 5) ? 128 : 0;

    touchData32[30] = GET_BIT(t0, 0) ? 128 : 0;
    touchData32[31] = GET_BIT(t0, 4) ? 128 : 0;
}

void updateTouch_v1() {

    uint16_t t0, t1, t2;
    if (ControllerConfig.cfg0 & CFG0_BIT_MBR3116) {
        MBR3116A.get_BUTTON_STAT((uint8_t*)&t0);
        MBR3116B.get_BUTTON_STAT((uint8_t*)&t1);
        MBR3116C.get_BUTTON_STAT((uint8_t*)&t2);
    } else {
        t0 = mpr0.touched();
        t1 = mpr1.touched();
        t2 = mpr2.touched();
    }

    touchData[0] = t0;
    touchData[1] = t1;
    touchData[2] = t2;
    touchData[3] = ((t0 & 0x0f00) >> 8) | ((t1 & 0x0f00) >> 4);

    touchData32[0] = GET_BIT(t1, 11) ? 128 : 0;
    touchData32[1] = GET_BIT(t1, 0) ? 128 : 0;

    touchData32[2] = GET_BIT(t1, 10) ? 128 : 0;
    touchData32[3] = GET_BIT(t1, 1) ? 128 : 0;

    touchData32[4] = GET_BIT(t1, 9) ? 128 : 0;
    touchData32[5] = GET_BIT(t1, 2) ? 128 : 0;

    touchData32[6] = GET_BIT(t1, 8) ? 128 : 0;
    touchData32[7] = GET_BIT(t1, 3) ? 128 : 0;

    touchData32[8] = GET_BIT(t0, 11) ? 128 : 0;
    touchData32[9] = GET_BIT(t1, 4) ? 128 : 0;

    touchData32[10] = GET_BIT(t0, 10) ? 128 : 0;
    touchData32[11] = GET_BIT(t1, 5) ? 128 : 0;

    touchData32[12] = GET_BIT(t0, 9) ? 128 : 0;
    touchData32[13] = GET_BIT(t1, 6) ? 128 : 0;

    touchData32[14] = GET_BIT(t0, 8) ? 128 : 0;
    touchData32[15] = GET_BIT(t1, 7) ? 128 : 0;

    touchData32[16] = GET_BIT(t0, 7) ? 128 : 0;
    touchData32[17] = GET_BIT(t2, 0) ? 128 : 0;

    touchData32[18] = GET_BIT(t0, 6) ? 128 : 0;
    touchData32[19] = GET_BIT(t2, 1) ? 128 : 0;

    touchData32[20] = GET_BIT(t0, 5) ? 128 : 0;
    touchData32[21] = GET_BIT(t2, 2) ? 128 : 0;

    touchData32[22] = GET_BIT(t0, 4) ? 128 : 0;
    touchData32[23] = GET_BIT(t2, 3) ? 128 : 0;

    touchData32[24] = GET_BIT(t0, 3) ? 128 : 0;
    touchData32[25] = GET_BIT(t2, 4) ? 128 : 0;

    touchData32[26] = GET_BIT(t0, 2) ? 128 : 0;
    touchData32[27] = GET_BIT(t2, 5) ? 128 : 0;

    touchData32[28] = GET_BIT(t0, 1) ? 128 : 0;
    touchData32[29] = GET_BIT(t2, 6) ? 128 : 0;

    touchData32[30] = GET_BIT(t0, 0) ? 128 : 0;
    touchData32[31] = GET_BIT(t2, 7) ? 128 : 0;
}

void updateTouchData4k() {
    for (uint8_t i = 0; i < 4; i++) {
        touchData4k[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            touchData4k[i] |= touchData32[i * 8 + j];
        }
    }
}

void updateTouchData6k() {
    for (uint8_t i = 0; i < 6; i++)
        touchData6k[i] = 0;

    for (uint8_t i = 29; i > 25; i--) {
        touchData6k[0] |= touchData32[i];
    }
    for (uint8_t i = 25; i > 21; i--) {
        touchData6k[1] |= touchData32[i];
    }
    for (uint8_t i = 21; i > 17; i--) {
        touchData6k[2] |= touchData32[i];
    }
    for (uint8_t i = 13; i > 9; i--) {
        touchData6k[3] |= touchData32[i];
    }
    for (uint8_t i = 9; i > 5; i--) {
        touchData6k[4] |= touchData32[i];
    }
    for (uint8_t i = 5; i > 1; i--) {
        touchData6k[5] |= touchData32[i];
    }
}

uint16_t heightDataOriginal[5] = { 4095, 4095, 4095, 4095, 4095 };
int16_t heightData[5] = { 4094, 4094, 4094, 4094, 4094 };
bool airKeys[6];

uint8_t heightRange = 10;

void updateAir() {
    bool updated = false;
    mux0.setChannel(0);
    if (tof0.readRangeContinuousMillimetersAsync(heightDataOriginal + 0)) {
        heightData[0] = heightDataOriginal[0];
        heightData[0] += ControllerConfig.heightOffset[0];
        updated = true;
    }
    mux0.setChannel(1);
    if (tof1.readRangeContinuousMillimetersAsync(heightDataOriginal + 1)) {
        heightData[1] = heightDataOriginal[1];
        heightData[1] += ControllerConfig.heightOffset[1];
        updated = true;
    }
    mux0.setChannel(2);
    if (tof2.readRangeContinuousMillimetersAsync(heightDataOriginal + 2)) {
        heightData[2] = heightDataOriginal[2];
        heightData[2] += ControllerConfig.heightOffset[2];
        updated = true;
    }
    mux0.setChannel(3);
    if (tof3.readRangeContinuousMillimetersAsync(heightDataOriginal + 3)) {
        heightData[3] = heightDataOriginal[3];
        heightData[3] += ControllerConfig.heightOffset[3];
        updated = true;
    }
    if (ControllerConfig.hwVer == 2 || ControllerConfig.hwVer == 4) {
        mux0.setChannel(4);
        if (tof4.readRangeContinuousMillimetersAsync(heightDataOriginal + 4)) {
            heightData[4] = heightDataOriginal[4];
            heightData[4] += ControllerConfig.heightOffset[4];
            updated = true;
        }
    }
    if (!updated) {
        return;
    }
    // 统计有效高度, 此处应为 dH = (..) / 6, 优化为dH = (..) * 21 / 128
    int16_t dH = ((ControllerConfig.airMax - ControllerConfig.airMin) * 21) >> 7;
    for (int j = 0; j < 6; j++) {
        bool detected = false;
        for (int i = 0; i < 5; i++) {
            if (ControllerConfig.airMin + dH * j - heightRange <= heightData[i] && ControllerConfig.airMin + dH * (j + 1) + heightRange >= heightData[i]) {
                detected = true;
                break;
            }
        }
        airKeys[j] = detected;
    }
}

void updateInputState() {
    if (ControllerConfig.hwVer == 1 || ControllerConfig.hwVer == 2) {
        updateTouch_v1();
    }
    if (ControllerConfig.hwVer == 3 || ControllerConfig.hwVer == 4) {
        updateTouch_v2();
    }
    if (usingIR) {
        updateIR();
    } else {
        updateAir();
    }
}