/* Modified from https://github.com/sebastianregelmann/CypressCY8CMBR3116 */
/*
MIT License

Copyright (c) 2025 sebastianregelmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <cy8cmbr3116.h>

CY8CMBR3116::CY8CMBR3116(uint8_t _i2c_port, uint8_t I2C_ADDRESS) {
    i2c_port = _i2c_port;
    DEVICE_I2C_ADDRESS = I2C_ADDRESS;
}

// SENSOR EN
uint8_t CY8CMBR3116::get_SENSOR_EN(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSOR_EN_ADDRESS, 2, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSOR_EN(uint8_t* dataBuffer) {
    return writeData(SENSOR_EN_ADDRESS, 2, dataBuffer);
}

// FFS EN
uint8_t CY8CMBR3116::get_FFS_EN(uint8_t* resultBuffer) {
    return requestDataFromAddress(FSS_EN_ADDRESS, 2, resultBuffer);
}
uint8_t CY8CMBR3116::set_FFS_EN(uint8_t* dataBuffer) {
    return writeData(FSS_EN_ADDRESS, 2, dataBuffer);
}

// TOGGLE EN
uint8_t CY8CMBR3116::get_TOGGLE_EN(uint8_t* resultBuffer) {
    return requestDataFromAddress(TOGGLE_EN_ADDRESS, 2, resultBuffer);
}
uint8_t CY8CMBR3116::set_TOGGLE_EN(uint8_t* dataBuffer) {
    return writeData(TOGGLE_EN_ADDRESS, 2, dataBuffer);
}

// LED_ON_EN_BUFFER
uint8_t CY8CMBR3116::get_LED_ON_EN(uint8_t* resultBuffer) {
    return requestDataFromAddress(LED_ON_EN_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_LED_ON_EN(uint8_t* dataBuffer) {
    return writeData(LED_ON_EN_ADDRESS, 1, dataBuffer);
}

// SENSITIVITY SETTINGS
uint8_t CY8CMBR3116::get_SENSITIVITY_0(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSITIVITY_0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSITIVITY_0(uint8_t* dataBuffer) {
    return writeData(SENSITIVITY_0_ADDRESS, 1, dataBuffer);
}
uint8_t CY8CMBR3116::get_SENSITIVITY_1(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSITIVITY_1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSITIVITY_1(uint8_t* dataBuffer) {
    return writeData(SENSITIVITY_1_ADDRESS, 1, dataBuffer);
}
uint8_t CY8CMBR3116::get_SENSITIVITY_2(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSITIVITY_2_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSITIVITY_2(uint8_t* dataBuffer) {
    return writeData(SENSITIVITY_2_ADDRESS, 1, dataBuffer);
}
uint8_t CY8CMBR3116::get_SENSITIVITY_3(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSITIVITY_3_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSITIVITY_3(uint8_t* dataBuffer) {
    return writeData(SENSITIVITY_3_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_SENSITIVITY_all(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSITIVITY_0_ADDRESS, 4, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSITIVITY_all(uint8_t* dataBuffer) {
    return writeData(SENSITIVITY_0_ADDRESS, 4, dataBuffer);
}

// Thresholds
uint8_t CY8CMBR3116::get_THRESHOLD(uint8_t* resultBuffer) {
    return requestDataFromAddress(THRESHOLD_ADDRESS, 16, resultBuffer);
}
uint8_t CY8CMBR3116::set_THRESHOLD(uint8_t* dataBuffer) {
    return writeData(THRESHOLD_ADDRESS, 16, dataBuffer);
}

// Button Tuning Settings
uint8_t CY8CMBR3116::get_SENSOR_DEBOUNCE(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSOR_DEBOUNCE_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSOR_DEBOUNCE(uint8_t* dataBuffer) {
    return writeData(SENSOR_DEBOUNCE_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_BUTTON_HYS(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUTTON_HYS_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_BUTTON_HYS(uint8_t* dataBuffer) {
    return writeData(BUTTON_HYS_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_BUTTON_LBR(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUTTON_LBR_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_BUTTON_LBR(uint8_t* dataBuffer) {
    return writeData(BUTTON_LBR_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_BUTTON_NNT(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUTTON_NNT_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_BUTTON_NNT(uint8_t* dataBuffer) {
    return writeData(BUTTON_NNT_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_BUTTON_NT(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUTTON_NT_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_BUTTON_NT(uint8_t* dataBuffer) {
    return writeData(BUTTON_NT_ADDRESS, 1, dataBuffer);
}

// Proximity Config Settings
uint8_t CY8CMBR3116::get_PROX_EN(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_EN_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_EN(uint8_t* dataBuffer) {
    return writeData(PROX_EN_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_CFG(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_CFG_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_CFG(uint8_t* dataBuffer) {
    return writeData(PROX_CFG_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_CFG2(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_CFG2_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_CFG2(uint8_t* dataBuffer) {
    return writeData(PROX_CFG2_ADDRESS, 1, dataBuffer);
}

// Proximity Thresholds
uint8_t CY8CMBR3116::get_PROX_TOUCH_TH0(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_TOUCH_TH0_ADDRESS, 2, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_TOUCH_TH0(uint8_t* dataBuffer) {
    return writeData(PROX_TOUCH_TH0_ADDRESS, 2, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_TOUCH_TH1(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_TOUCH_TH1_ADDRESS, 2, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_TOUCH_TH1(uint8_t* dataBuffer) {
    return writeData(PROX_TOUCH_TH1_ADDRESS, 2, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_POSITIVE_TH_0(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_POSITIVE_TH_0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_POSITIVE_TH_0(uint8_t* dataBuffer) {
    return writeData(PROX_POSITIVE_TH_0_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_POSITIVE_TH_1(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_POSITIVE_TH_1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_POSITIVE_TH_1(uint8_t* dataBuffer) {
    return writeData(PROX_POSITIVE_TH_1_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_NEGATIVE_TH_0(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_NEGATIVE_TH_0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_NEGATIVE_TH_0(uint8_t* dataBuffer) {
    return writeData(PROX_NEGATIVE_TH_0_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_NEGATIVE_TH_1(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_NEGATIVE_TH_1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_NEGATIVE_TH_1(uint8_t* dataBuffer) {
    return writeData(PROX_NEGATIVE_TH_1_ADDRESS, 1, dataBuffer);
}

// Proximity Resolution
uint8_t CY8CMBR3116::get_PROX_RESOLUTION0(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_RESOLUTION0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_RESOLUTION0(uint8_t* dataBuffer) {
    return writeData(PROX_RESOLUTION0_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_RESOLUTION1(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_RESOLUTION1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_RESOLUTION1(uint8_t* dataBuffer) {
    return writeData(PROX_RESOLUTION1_ADDRESS, 1, dataBuffer);
}

// Proximity Tuning Settings
uint8_t CY8CMBR3116::get_PROX_HYS(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_HYS_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_HYS(uint8_t* dataBuffer) {
    return writeData(PROX_HYS_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_LBR(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_LBR_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_LBR(uint8_t* dataBuffer) {
    return writeData(PROX_LBR_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_NNT(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_NNT_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_NNT(uint8_t* dataBuffer) {
    return writeData(PROX_NNT_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PROX_NT(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_NT_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PROX_NT(uint8_t* dataBuffer) {
    return writeData(PROX_NT_ADDRESS, 1, dataBuffer);
}

// LED Settings
uint8_t CY8CMBR3116::get_LED_ON_TIME(uint8_t* resultBuffer) {
    return requestDataFromAddress(LED_ON_TIME_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_LED_ON_TIME(uint8_t* dataBuffer) {
    return writeData(LED_ON_TIME_ADDRESS, 1, dataBuffer);
}

// BUZZER Settings
uint8_t CY8CMBR3116::get_BUZZER_CFG(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUZZER_CFG_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_BUZZER_CFG(uint8_t* dataBuffer) {
    return writeData(BUZZER_CFG_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_BUZZER_ON_TIME(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUZZER_ON_TIME_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_BUZZER_ON_TIME(uint8_t* dataBuffer) {
    return writeData(BUZZER_ON_TIME_ADDRESS, 1, dataBuffer);
}

// GPO Settings
uint8_t CY8CMBR3116::get_GPO_CFG(uint8_t* resultBuffer) {
    return requestDataFromAddress(GPO_CFG_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_GPO_CFG(uint8_t* dataBuffer) {
    return writeData(GPO_CFG_ADDRESS, 1, dataBuffer);
}

// PWM Settings
uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG0(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG0(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG0_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG1(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG1(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG1_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG2(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG2_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG2(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG2_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG3(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG3_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG3(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG3_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG4(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG4_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG4(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG4_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG5(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG5_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG5(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG5_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG6(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG6_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG6(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG6_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_PWM_DUTYCYCLE_CFG7(uint8_t* resultBuffer) {
    return requestDataFromAddress(PWM_DUTYCYCLE_CFG7_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_PWM_DUTYCYCLE_CFG7(uint8_t* dataBuffer) {
    return writeData(PWM_DUTYCYCLE_CFG7_ADDRESS, 1, dataBuffer);
}

// Config Settings
uint8_t CY8CMBR3116::get_SPO_CFG(uint8_t* resultBuffer) {
    return requestDataFromAddress(SPO_CFG_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SPO_CFG(uint8_t* dataBuffer) {
    return writeData(SPO_CFG_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_DEVICE_CFG0(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEVICE_CFG0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_DEVICE_CFG0(uint8_t* dataBuffer) {
    return writeData(DEVICE_CFG0_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_DEVICE_CFG1(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEVICE_CFG1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_DEVICE_CFG1(uint8_t* dataBuffer) {
    return writeData(DEVICE_CFG1_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_DEVICE_CFG2(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEVICE_CFG2_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_DEVICE_CFG2(uint8_t* dataBuffer) {
    return writeData(DEVICE_CFG2_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_DEVICE_CFG3(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEVICE_CFG3_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_DEVICE_CFG3(uint8_t* dataBuffer) {
    return writeData(DEVICE_CFG3_ADDRESS, 1, dataBuffer);
}

// I2C Address
uint8_t CY8CMBR3116::get_I2C_ADDR(uint8_t* resultBuffer) {
    return requestDataFromAddress(I2C_ADDR_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_I2C_ADDR(uint8_t* dataBuffer) {
    return writeData(I2C_ADDR_ADDRESS, 1, dataBuffer);
}

// Refresh Rate
uint8_t CY8CMBR3116::get_REFRESH_CTRL(uint8_t* resultBuffer) {
    return requestDataFromAddress(REFRESH_CTRL_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_REFRESH_CTRL(uint8_t* dataBuffer) {
    return writeData(REFRESH_CTRL_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_STATE_TIMEOUT(uint8_t* resultBuffer) {
    return requestDataFromAddress(STATE_TIMEOUT_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_STATE_TIMEOUT(uint8_t* dataBuffer) {
    return writeData(STATE_TIMEOUT_ADDRESS, 1, dataBuffer);
}

// Scratchpad Settings
uint8_t CY8CMBR3116::get_SCRATCHPAD0(uint8_t* resultBuffer) {
    return requestDataFromAddress(SCRATCHPAD0_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SCRATCHPAD0(uint8_t* dataBuffer) {
    return writeData(SCRATCHPAD0_ADDRESS, 1, dataBuffer);
}

uint8_t CY8CMBR3116::get_SCRATCHPAD1(uint8_t* resultBuffer) {
    return requestDataFromAddress(SCRATCHPAD1_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SCRATCHPAD1(uint8_t* dataBuffer) {
    return writeData(SCRATCHPAD1_ADDRESS, 1, dataBuffer);
}

// Config CRC Settings
uint8_t CY8CMBR3116::get_CONFIG_CRC(uint8_t* resultBuffer) {
    return requestDataFromAddress(CONFIG_CRC_ADDRESS, 2, resultBuffer);
}
uint8_t CY8CMBR3116::set_CONFIG_CRC(uint8_t* dataBuffer) {
    return writeData(CONFIG_CRC_ADDRESS, 2, dataBuffer);
}

// Read-only
uint8_t CY8CMBR3116::get_CALC_CRC(uint8_t* resultBuffer) {
    return requestDataFromAddress(CALC_CRC_ADDRESS, 2, resultBuffer);
}
// GPO Output State
uint8_t CY8CMBR3116::get_GPO_OUTPUT_STATE(uint8_t* resultBuffer) {
    return requestDataFromAddress(GPO_OUTPUT_STATE_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_GPO_OUTPUT_STATE(uint8_t* dataBuffer) {
    return writeData(GPO_OUTPUT_STATE_ADDRESS, 1, dataBuffer);
}

// Sensor ID
uint8_t CY8CMBR3116::get_SENSOR_ID(uint8_t* resultBuffer) {
    return requestDataFromAddress(SENSOR_ID_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_SENSOR_ID(uint8_t* dataBuffer) {
    return writeData(SENSOR_ID_ADDRESS, 1, dataBuffer);
}

// Read-only
uint8_t CY8CMBR3116::get_FAMILY_ID(uint8_t* resultBuffer) {
    return requestDataFromAddress(FAMILY_ID_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_DEVICE_ID(uint16_t* resultBuffer) {

    uint8_t tmp[2];
    uint8_t error = requestDataFromAddress(DEVICE_ID_ADDRESS, 2, tmp);
    // Convert 2 uint8 to uint16
    uint8_t msb = tmp[1];
    uint8_t lsb = tmp[0];
    resultBuffer[0] = msb << 8 | lsb;

    return error;
}

uint8_t CY8CMBR3116::get_DEVICE_REV(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEVICE_REV_ADDRESS, 1, resultBuffer);
}

// Control CMD Buffer
uint8_t CY8CMBR3116::get_CTRL_CMD(uint8_t* resultBuffer) {
    return requestDataFromAddress(CTRL_CMD_ADDRESS, 1, resultBuffer);
}
uint8_t CY8CMBR3116::set_CTRL_CMD(uint8_t* dataBuffer) {
    return writeData(CTRL_CMD_ADDRESS, 1, dataBuffer);
}

// Read-only
uint8_t CY8CMBR3116::get_CTRL_CMD_STATUS(uint8_t* resultBuffer) {
    return requestDataFromAddress(CTRL_CMD_STATUS_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_CTRL_CMD_ERR(uint8_t* resultBuffer) {
    return requestDataFromAddress(CTRL_CMD_ERR_ADDRESS, 1, resultBuffer);
}

// System Status (Read-only)
uint8_t CY8CMBR3116::get_SYSTEM_STATUS(uint8_t* resultBuffer) {
    return requestDataFromAddress(SYSTEM_STATUS_ADDRESS, 1, resultBuffer);
}

// Previous Control CMD Code (Read-only)
uint8_t CY8CMBR3116::get_PREV_CTRL_CMD_CODE(uint8_t* resultBuffer) {
    return requestDataFromAddress(PREV_CTRL_CMD_CODE_ADDRESS, 1, resultBuffer);
}

// Number of Working Sensors
uint8_t CY8CMBR3116::get_TOTAL_WORKING_SNS(uint8_t* resultBuffer) {
    return requestDataFromAddress(TOTAL_WORKING_SNS_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_SNS_CP_HIGH(uint8_t* resultBuffer) {
    return requestDataFromAddress(SNS_CP_HIGH_ADDRESS, 2, resultBuffer);
}

uint8_t CY8CMBR3116::get_SNS_VDD_SHORT(uint8_t* resultBuffer) {
    return requestDataFromAddress(SNS_VDD_SHORT_ADDRESS, 2, resultBuffer);
}

uint8_t CY8CMBR3116::get_SNS_GND_SHORT(uint8_t* resultBuffer) {
    return requestDataFromAddress(SNS_GND_SHORT_ADDRESS, 2, resultBuffer);
}

uint8_t CY8CMBR3116::get_SNS_SNS_SHORT(uint8_t* resultBuffer) {
    return requestDataFromAddress(SNS_SNS_SHORT_ADDRESS, 2, resultBuffer);
}

uint8_t CY8CMBR3116::get_CMOD_SHIELD_TEST(uint8_t* resultBuffer) {
    return requestDataFromAddress(CMOD_SHIELD_TEST_ADDRESS, 1, resultBuffer);
}

// Button Status
uint8_t CY8CMBR3116::get_BUTTON_STAT(uint8_t* resultBuffer) {
    return requestDataFromAddress(BUTTON_STAT_ADDRESS, 2, resultBuffer);
}

uint8_t CY8CMBR3116::get_LATCHED_BUTTON_STAT(uint8_t* resultBuffer) {
    return requestDataFromAddress(LATCHED_BUTTON_STAT_ADDRESS, 2, resultBuffer);
}

// Proximity Status
uint8_t CY8CMBR3116::get_PROX_STAT(uint8_t* resultBuffer) {
    return requestDataFromAddress(PROX_STAT_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_LATCHED_PROX_STAT(uint8_t* resultBuffer) {
    return requestDataFromAddress(LATCHED_PROX_STAT_ADDRESS, 1, resultBuffer);
}

// Sync Counter
uint8_t CY8CMBR3116::get_SYNC_COUNTER0(uint8_t* resultBuffer) {
    return requestDataFromAddress(SYNC_COUNTER0_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_SYNC_COUNTER1(uint8_t* resultBuffer) {
    return requestDataFromAddress(SYNC_COUNTER1_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_SYNC_COUNTER2(uint8_t* resultBuffer) {
    return requestDataFromAddress(SYNC_COUNTER2_ADDRESS, 1, resultBuffer);
}

// Differences for Each Sensor Counter
uint8_t CY8CMBR3116::get_DIFFERENCE_COUNT_SENSOR(uint16_t* resultBuffer) {
    uint8_t tmp[32];
    uint8_t error = requestDataFromAddress(DIFFERENCE_COUNT_SENSOR_ADDRESS, 32, tmp);
    // Convert the 32*uint8_t buffer to 1 16*uint16_t buffer
    for (uint8_t i = 0; i < 16; i++) {
        uint8_t msb = tmp[i * 2 + 1];
        uint8_t lsb = tmp[i * 2];
        resultBuffer[i] = msb << 8 | lsb;
    }

    return error;
}

// GPO Data
uint8_t CY8CMBR3116::get_GPO_DATA(uint8_t* resultBuffer) {
    return requestDataFromAddress(GPO_DATA_ADDRESS, 1, resultBuffer);
}

// Debug Data
uint8_t CY8CMBR3116::get_DEBUG_SENSOR_ID(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEBUG_SENSOR_ID_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_DEBUG_CP(uint8_t* resultBuffer) {
    return requestDataFromAddress(DEBUG_CP_ADDRESS, 1, resultBuffer);
}

uint8_t CY8CMBR3116::get_DEBUG_DIFFERENCE_COUNT0(uint16_t* resultBuffer) {
    uint8_t tmp[2];
    uint8_t error = requestDataFromAddress(DEBUG_DIFFERENCE_COUNT0_ADDRESS, 2, tmp);
    // Convert 2 uint8 to uint16
    uint8_t msb = tmp[1];
    uint8_t lsb = tmp[0];
    resultBuffer[0] = msb << 8 | lsb;

    return error;
}

uint8_t CY8CMBR3116::get_DEBUG_BASELINE0(uint16_t* resultBuffer) {
    uint8_t tmp[2];
    uint8_t error = requestDataFromAddress(DEBUG_BASELINE0_ADDRESS, 2, tmp);
    // Convert 2 uint8 to uint16
    uint8_t msb = tmp[1];
    uint8_t lsb = tmp[0];
    resultBuffer[0] = msb << 8 | lsb;

    return error;
}

uint8_t CY8CMBR3116::get_DEBUG_RAW_COUNT0(uint16_t* resultBuffer) {
    uint8_t tmp[2];
    uint8_t error = requestDataFromAddress(DEBUG_RAW_COUNT0_ADDRESS, 2, tmp);
    // Convert 2 uint8 to uint16
    uint8_t msb = tmp[1];
    uint8_t lsb = tmp[0];
    resultBuffer[0] = msb << 8 | lsb;

    return error;
}

uint8_t CY8CMBR3116::get_DEBUG_AVG_RAW_COUNT0(uint16_t* resultBuffer) {
    uint8_t tmp[2];
    uint8_t error = requestDataFromAddress(DEBUG_AVG_RAW_COUNT0_ADDRESS, 2, tmp);
    // Convert 2 uint8 to uint16
    uint8_t msb = tmp[1];
    uint8_t lsb = tmp[0];
    resultBuffer[0] = msb << 8 | lsb;

    return error;
}

// METHODS FOR WRITING/READING AND SETTING POINTER ON IC
uint8_t CY8CMBR3116::setPointer(int registerAddress) {
    // uint8_t error = 5;
    // uint8_t timeoutCounter = 0;

    // while (error != 0 && timeoutCounter < TIMEOUTCOUNTER) {
    // Begin transmission to the device
    // Wire.beginTransmission(DEVICE_I2C_ADDRESS);
    // Set the register pointer
    // Wire.write(registerAddress);
    // End transmission
    // error = Wire.endTransmission();
    uint8_t buf = registerAddress;
    i2c_write(i2c_port, DEVICE_I2C_ADDRESS, &buf, 1, false);

    // timeoutCounter++;
    // }

    // return error;
    return 0;
}

// Method to retriev count of bytes from last pointer Postition to resultBuffer
uint8_t CY8CMBR3116::requestData(uint8_t count, uint8_t* resultBuffer) {

    // uint8_t timeoutCounter = 0;
    // return request from the IC
    // while (Wire.available() == 0 && timeoutCounter < TIMEOUTCOUNTER) {
    // while (timeoutCounter < TIMEOUTCOUNTER) {
    // Wire.requestFrom(DEVICE_I2C_ADDRESS, count);
    i2c_read(i2c_port, DEVICE_I2C_ADDRESS, resultBuffer, count, false);
    // timeoutCounter++;
    // }

    // check if timeout occured
    // if (timeoutCounter >= TIMEOUTCOUNTER) {
    // return 5;
    // }

    // Read the return requested Data
    // uint8_t counter = 0;
    // while (Wire.available()) {
    //     resultBuffer[counter] = Wire.read();
    //     counter++;
    // }

    return 0;
}

// Method to write uint8_tCount of uint8_ts to a registerAddress from the data buffer
uint8_t CY8CMBR3116::writeData(uint8_t registerAddress, uint8_t count, uint8_t* data) {
    // uint8_t error = 5;
    // uint8_t timeoutCounter = 0;

    // while (error != 0 && timeoutCounter < TIMEOUTCOUNTER) {
    // Begin transmission to the device
    // Wire.beginTransmission(DEVICE_I2C_ADDRESS);

    uint8_t* buf = new uint8_t[count + 1];
    buf[0] = registerAddress;
    for (int i = 0; i < count; i++) {
        buf[i + 1] = data[i];
    }

    i2c_write(i2c_port, DEVICE_I2C_ADDRESS, buf, count + 1, false);

    // Set the register pointer
    // Wire.write(registerAddress);

    // write the uint8_ts
    // for (uint8_t i = 0; i < count; i++) {
    // Wire.write(data[i]);
    // }
    // End transmission
    // error = Wire.endTransmission();

    // timeoutCounter++;
    // }
    // return error;
    return 0;
}

// Method to retriev uint8_tCount of uint8_ts from an registerAddress to the resultBuffer
uint8_t CY8CMBR3116::requestDataFromAddress(uint8_t registerAddress, uint8_t count, uint8_t* resultBuffer) {
    // Set the pointer
    uint8_t error;
    error = setPointer(registerAddress);
    if (error == 0) {
        // return request the Data
        error = requestData(count, resultBuffer);
    }

    return error;
}

uint8_t CY8CMBR3116::applyRegister() {
    uint8_t tmp[1] = { 2 };
    return writeData(CTRL_CMD_ADDRESS, 1, tmp);
}

uint8_t CY8CMBR3116::calculateCRC() {
    uint8_t tmp[1] = { 3 };
    return writeData(CTRL_CMD_ADDRESS, 1, tmp);
}

uint8_t CY8CMBR3116::enterLowPower() {
    uint8_t tmp[1] = { 7 };
    return writeData(CTRL_CMD_ADDRESS, 1, tmp);
}

uint8_t CY8CMBR3116::resetIC() {
    uint8_t tmp[1] = { 255 };
    return writeData(CTRL_CMD_ADDRESS, 1, tmp);
}

uint8_t CY8CMBR3116::activateSettings() {
    uint8_t crc_buffer[2];
    // calculate CRC
    uint8_t error = calculateCRC();

    // read the calculated CRC
    if (error == 0) {
        error = get_CALC_CRC(crc_buffer);
    }

    // set the calculated CRC
    if (error == 0) {
        error = set_CONFIG_CRC(crc_buffer);
    }

    // Apply the register
    if (error == 0) {
        error = applyRegister();
    }

    // reset the IC
    if (error == 0) {
        error = resetIC();
    }

    return error;
}

uint8_t cy8cmbr3116_cfg_0x37[128] = { 0xFFu, 0x0Fu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
                                      0x80u, 0x80u, 0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x03u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x05u, 0x00u, 0x00u, 0x02u,
                                      0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u, 0xFFu,
                                      0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u, 0x03u, 0x01u, 0x48u, 0x00u, 0x37u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xADu, 0x32u };

uint8_t cy8cmbr3116_cfg_0x40[128] = { 0xFFu, 0x0Fu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
                                      0x80u, 0x80u, 0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x05u, 0x00u, 0x00u, 0x02u,
                                      0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u, 0xFFu,
                                      0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x68u, 0x00u, 0x40u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x34u, 0x5Du };

uint8_t cy8cmbr3116_cfg_0x41[128] = { 0xFFu, 0x0Fu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
                                      0x80u, 0x80u, 0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x05u, 0x00u, 0x00u, 0x02u,
                                      0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u, 0xFFu,
                                      0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x68u, 0x00u, 0x41u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x17u, 0x89u };

uint8_t cy8cmbr3116_cfg_0x42[128] = { 0xFFu, 0x0Fu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
                                      0x80u, 0x80u, 0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x05u, 0x00u, 0x00u, 0x02u,
                                      0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u, 0xFFu,
                                      0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x68u, 0x00u, 0x42u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x53u, 0xE5u };

uint8_t cy8cmbr3116_cfg_0x43[128] = { 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
                                      0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x05u, 0x00u, 0x00u, 0x02u,
                                      0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u, 0xFFu,
                                      0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x10u, 0x00u, 0x01u, 0x68u, 0x00u, 0x43u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x72u, 0x68u };

uint8_t cy8cmbr3116_cfg_0x44[128] = { 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
                                      0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u, 0x05u, 0x00u, 0x00u, 0x02u,
                                      0x00u, 0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u, 0xFFu,
                                      0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x10u, 0x00u, 0x01u, 0x68u, 0x00u, 0x44u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
                                      0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xD9u, 0x64u };
