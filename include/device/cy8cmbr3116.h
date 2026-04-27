#ifndef CYPRESSCY8CMBR3116_H
#define CYPRESSCY8CMBR3116_H

#include <i2c_port.h>
#include <stdint-gcc.h>

// REGISTEr ADDRESES
//  Active Sensor Settings
#define SENSOR_EN_ADDRESS 0x00
#define FSS_EN_ADDRESS 0x02
#define TOGGLE_EN_ADDRESS 0x04
#define LED_ON_EN_ADDRESS 0x06

// Sensitivity Settings
#define SENSITIVITY_0_ADDRESS 0x08
#define SENSITIVITY_1_ADDRESS 0x09
#define SENSITIVITY_2_ADDRESS 0x0a
#define SENSITIVITY_3_ADDRESS 0x0b

// Threshold Settings
#define THRESHOLD_ADDRESS 0x0c

// Button Tuning Settings
#define SENSOR_DEBOUNCE_ADDRESS 0x1c
#define BUTTON_HYS_ADDRESS 0x1d
#define BUTTON_LBR_ADDRESS 0x1f
#define BUTTON_NNT_ADDRESS 0x20
#define BUTTON_NT_ADDRESS 0x21

// Proximity Config Settings
#define PROX_EN_ADDRESS 0x26
#define PROX_CFG_ADDRESS 0x27
#define PROX_CFG2_ADDRESS 0x28

// Proximity Thresholds
#define PROX_TOUCH_TH0_ADDRESS 0x2a
#define PROX_TOUCH_TH1_ADDRESS 0x2c
#define PROX_POSITIVE_TH_0_ADDRESS 0x35
#define PROX_POSITIVE_TH_1_ADDRESS 0x36
#define PROX_NEGATIVE_TH_0_ADDRESS 0x39
#define PROX_NEGATIVE_TH_1_ADDRESS 0x3a

// Proximity Resolution
#define PROX_RESOLUTION0_ADDRESS 0x2e
#define PROX_RESOLUTION1_ADDRESS 0x2f

// Proximity Tuning Settings
#define PROX_HYS_ADDRESS 0x30
#define PROX_LBR_ADDRESS 0x32
#define PROX_NNT_ADDRESS 0x33
#define PROX_NT_ADDRESS 0x34

// LED Settings
#define LED_ON_TIME_ADDRESS 0x3d

// Buzzer Settings
#define BUZZER_CFG_ADDRESS 0x3e
#define BUZZER_ON_TIME_ADDRESS 0x3f

// GPO Settings
#define GPO_CFG_ADDRESS 0x40

// PWM Settings
#define PWM_DUTYCYCLE_CFG0_ADDRESS 0x41
#define PWM_DUTYCYCLE_CFG1_ADDRESS 0x42
#define PWM_DUTYCYCLE_CFG2_ADDRESS 0x43
#define PWM_DUTYCYCLE_CFG3_ADDRESS 0x44
#define PWM_DUTYCYCLE_CFG4_ADDRESS 0x45
#define PWM_DUTYCYCLE_CFG5_ADDRESS 0x46
#define PWM_DUTYCYCLE_CFG6_ADDRESS 0x47
#define PWM_DUTYCYCLE_CFG7_ADDRESS 0x48

// Config Settings
#define SPO_CFG_ADDRESS 0x4c
#define DEVICE_CFG0_ADDRESS 0x4d
#define DEVICE_CFG1_ADDRESS 0x4e
#define DEVICE_CFG2_ADDRESS 0x4f
#define DEVICE_CFG3_ADDRESS 0x50

// I2C Address
#define I2C_ADDR_ADDRESS 0x51

// Refresh Settings
#define REFRESH_CTRL_ADDRESS 0x52
#define STATE_TIMEOUT_ADDRESS 0x55

// Scratchpad settings
#define SCRATCHPAD0_ADDRESS 0x7a
#define SCRATCHPAD1_ADDRESS 0x7b

// Config CRC Address
#define CONFIG_CRC_ADDRESS 0x7e
#define CALC_CRC_ADDRESS 0x94

// GPO Output State
#define GPO_OUTPUT_STATE_ADDRESS 0x80

// Sensor IDs
#define SENSOR_ID_ADDRESS 0x82
#define FAMILY_ID_ADDRESS 0x8f
#define DEVICE_ID_ADDRESS 0x90
#define DEVICE_REV_ADDRESS 0x92

// Control Command Registers
#define CTRL_CMD_ADDRESS 0x86
#define CTRL_CMD_STATUS_ADDRESS 0x88
#define CTRL_CMD_ERR_ADDRESS 0x89

// System Status
#define SYSTEM_STATUS_ADDRESS 0x8a

// Previous Command Code
#define PREV_CTRL_CMD_CODE_ADDRESS 0x8c

// Working Sensors
#define TOTAL_WORKING_SNS_ADDRESS 0x97
#define SNS_CP_HIGH_ADDRESS 0x98
#define SNS_VDD_SHORT_ADDRESS 0x9a
#define SNS_GND_SHORT_ADDRESS 0x9c
#define SNS_SNS_SHORT_ADDRESS 0x9e
#define CMOD_SHIELD_TEST_ADDRESS 0xa0

// Button Status
#define BUTTON_STAT_ADDRESS 0xaa
#define LATCHED_BUTTON_STAT_ADDRESS 0xac

// Proximity Status
#define PROX_STAT_ADDRESS 0xae
#define LATCHED_PROX_STAT_ADDRESS 0xaf

// Sync Counter
#define SYNC_COUNTER0_ADDRESS 0xb9
#define SYNC_COUNTER1_ADDRESS 0xdb
#define SYNC_COUNTER2_ADDRESS 0xe7

// Sensor Difference
#define DIFFERENCE_COUNT_SENSOR_ADDRESS 0xba

// GPO Data
#define GPO_DATA_ADDRESS 0xda

// Debug Addresses
#define DEBUG_SENSOR_ID_ADDRESS 0xdc
#define DEBUG_CP_ADDRESS 0xdd
#define DEBUG_DIFFERENCE_COUNT0_ADDRESS 0xde
#define DEBUG_BASELINE0_ADDRESS 0xe0
#define DEBUG_RAW_COUNT0_ADDRESS 0xe2
#define DEBUG_AVG_RAW_COUNT0_ADDRESS 0xe4

class CY8CMBR3116 {
private:
    uint8_t DEVICE_I2C_ADDRESS;
    uint8_t TIMEOUTCOUNTER;
    uint8_t i2c_port;


public:
    // Constructor
    CY8CMBR3116(uint8_t _i2c_port,uint8_t I2C_ADDRESS);
    // Function Declarations
    uint8_t get_SENSOR_EN(uint8_t* resultBuffer);
    uint8_t set_SENSOR_EN(uint8_t* dataBuffer);

    uint8_t get_FFS_EN(uint8_t* resultBuffer);
    uint8_t set_FFS_EN(uint8_t* dataBuffer);

    uint8_t get_TOGGLE_EN(uint8_t* resultBuffer);
    uint8_t set_TOGGLE_EN(uint8_t* dataBuffer);

    uint8_t get_LED_ON_EN(uint8_t* resultBuffer);
    uint8_t set_LED_ON_EN(uint8_t* dataBuffer);

    uint8_t get_SENSITIVITY_0(uint8_t* resultBuffer);
    uint8_t set_SENSITIVITY_0(uint8_t* dataBuffer);
    uint8_t get_SENSITIVITY_1(uint8_t* resultBuffer);
    uint8_t set_SENSITIVITY_1(uint8_t* dataBuffer);
    uint8_t get_SENSITIVITY_2(uint8_t* resultBuffer);
    uint8_t set_SENSITIVITY_2(uint8_t* dataBuffer);
    uint8_t get_SENSITIVITY_3(uint8_t* resultBuffer);
    uint8_t set_SENSITIVITY_3(uint8_t* dataBuffer);

    uint8_t get_SENSITIVITY_all(uint8_t* resultBuffer);
    uint8_t set_SENSITIVITY_all(uint8_t* dataBuffer);

    uint8_t get_THRESHOLD(uint8_t* resultBuffer);
    uint8_t set_THRESHOLD(uint8_t* dataBuffer);

    uint8_t get_SENSOR_DEBOUNCE(uint8_t* resultBuffer);
    uint8_t set_SENSOR_DEBOUNCE(uint8_t* dataBuffer);

    uint8_t get_BUTTON_HYS(uint8_t* resultBuffer);
    uint8_t set_BUTTON_HYS(uint8_t* dataBuffer);

    uint8_t get_BUTTON_LBR(uint8_t* resultBuffer);
    uint8_t set_BUTTON_LBR(uint8_t* dataBuffer);

    uint8_t get_BUTTON_NNT(uint8_t* resultBuffer);
    uint8_t set_BUTTON_NNT(uint8_t* dataBuffer);

    uint8_t get_BUTTON_NT(uint8_t* resultBuffer);
    uint8_t set_BUTTON_NT(uint8_t* dataBuffer);

    uint8_t get_PROX_EN(uint8_t* resultBuffer);
    uint8_t set_PROX_EN(uint8_t* dataBuffer);

    uint8_t get_PROX_CFG(uint8_t* resultBuffer);
    uint8_t set_PROX_CFG(uint8_t* dataBuffer);

    uint8_t get_PROX_CFG2(uint8_t* resultBuffer);
    uint8_t set_PROX_CFG2(uint8_t* dataBuffer);

    uint8_t get_PROX_TOUCH_TH0(uint8_t* resultBuffer);
    uint8_t set_PROX_TOUCH_TH0(uint8_t* dataBuffer);

    uint8_t get_PROX_TOUCH_TH1(uint8_t* resultBuffer);
    uint8_t set_PROX_TOUCH_TH1(uint8_t* dataBuffer);

    uint8_t get_PROX_POSITIVE_TH_0(uint8_t* resultBuffer);
    uint8_t set_PROX_POSITIVE_TH_0(uint8_t* dataBuffer);

    uint8_t get_PROX_POSITIVE_TH_1(uint8_t* resultBuffer);
    uint8_t set_PROX_POSITIVE_TH_1(uint8_t* dataBuffer);

    uint8_t get_PROX_NEGATIVE_TH_0(uint8_t* resultBuffer);
    uint8_t set_PROX_NEGATIVE_TH_0(uint8_t* dataBuffer);

    uint8_t get_PROX_NEGATIVE_TH_1(uint8_t* resultBuffer);
    uint8_t set_PROX_NEGATIVE_TH_1(uint8_t* dataBuffer);

    uint8_t get_PROX_RESOLUTION0(uint8_t* resultBuffer);
    uint8_t set_PROX_RESOLUTION0(uint8_t* dataBuffer);

    uint8_t get_PROX_RESOLUTION1(uint8_t* resultBuffer);
    uint8_t set_PROX_RESOLUTION1(uint8_t* dataBuffer);

    uint8_t get_PROX_HYS(uint8_t* resultBuffer);
    uint8_t set_PROX_HYS(uint8_t* dataBuffer);

    uint8_t get_PROX_LBR(uint8_t* resultBuffer);
    uint8_t set_PROX_LBR(uint8_t* dataBuffer);

    uint8_t get_PROX_NNT(uint8_t* resultBuffer);
    uint8_t set_PROX_NNT(uint8_t* dataBuffer);

    uint8_t get_PROX_NT(uint8_t* resultBuffer);
    uint8_t set_PROX_NT(uint8_t* dataBuffer);

    uint8_t get_LED_ON_TIME(uint8_t* resultBuffer);
    uint8_t set_LED_ON_TIME(uint8_t* dataBuffer);

    uint8_t get_BUZZER_CFG(uint8_t* resultBuffer);
    uint8_t set_BUZZER_CFG(uint8_t* dataBuffer);

    uint8_t get_BUZZER_ON_TIME(uint8_t* resultBuffer);
    uint8_t set_BUZZER_ON_TIME(uint8_t* dataBuffer);

    uint8_t get_GPO_CFG(uint8_t* resultBuffer);
    uint8_t set_GPO_CFG(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG0(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG0(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG1(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG1(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG2(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG2(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG3(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG3(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG4(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG4(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG5(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG5(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG6(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG6(uint8_t* dataBuffer);

    uint8_t get_PWM_DUTYCYCLE_CFG7(uint8_t* resultBuffer);
    uint8_t set_PWM_DUTYCYCLE_CFG7(uint8_t* dataBuffer);

    uint8_t get_SPO_CFG(uint8_t* resultBuffer);
    uint8_t set_SPO_CFG(uint8_t* dataBuffer);

    uint8_t get_DEVICE_CFG0(uint8_t* resultBuffer);
    uint8_t set_DEVICE_CFG0(uint8_t* dataBuffer);

    uint8_t get_DEVICE_CFG1(uint8_t* resultBuffer);
    uint8_t set_DEVICE_CFG1(uint8_t* dataBuffer);

    uint8_t get_DEVICE_CFG2(uint8_t* resultBuffer);
    uint8_t set_DEVICE_CFG2(uint8_t* dataBuffer);

    uint8_t get_DEVICE_CFG3(uint8_t* resultBuffer);
    uint8_t set_DEVICE_CFG3(uint8_t* dataBuffer);

    uint8_t get_I2C_ADDR(uint8_t* resultBuffer);
    uint8_t set_I2C_ADDR(uint8_t* dataBuffer);

    uint8_t get_REFRESH_CTRL(uint8_t* resultBuffer);
    uint8_t set_REFRESH_CTRL(uint8_t* dataBuffer);

    uint8_t get_STATE_TIMEOUT(uint8_t* resultBuffer);
    uint8_t set_STATE_TIMEOUT(uint8_t* dataBuffer);

    uint8_t get_SCRATCHPAD0(uint8_t* resultBuffer);
    uint8_t set_SCRATCHPAD0(uint8_t* dataBuffer);

    uint8_t get_SCRATCHPAD1(uint8_t* resultBuffer);
    uint8_t set_SCRATCHPAD1(uint8_t* dataBuffer);

    uint8_t get_CONFIG_CRC(uint8_t* resultBuffer);
    uint8_t set_CONFIG_CRC(uint8_t* dataBuffer);

    uint8_t get_CALC_CRC(uint8_t* resultBuffer);
    uint8_t set_CALC_CRC(uint8_t* dataBuffer);

    uint8_t get_GPO_OUTPUT_STATE(uint8_t* resultBuffer);
    uint8_t set_GPO_OUTPUT_STATE(uint8_t* dataBuffer);

    uint8_t get_SENSOR_ID(uint8_t* resultBuffer);
    uint8_t set_SENSOR_ID(uint8_t* dataBuffer);
    uint8_t get_FAMILY_ID(uint8_t* resultBuffer);
    uint8_t get_DEVICE_ID(uint16_t* resultBuffer);
    uint8_t get_DEVICE_REV(uint8_t* resultBuffer);

    uint8_t get_CTRL_CMD(uint8_t* resultBuffer);
    uint8_t set_CTRL_CMD(uint8_t* dataBuffer);

    uint8_t get_CTRL_CMD_STATUS(uint8_t* resultBuffer);

    uint8_t get_CTRL_CMD_ERR(uint8_t* resultBuffer);

    uint8_t get_SYSTEM_STATUS(uint8_t* resultBuffer);

    uint8_t get_PREV_CTRL_CMD_CODE(uint8_t* resultBuffer);

    uint8_t get_TOTAL_WORKING_SNS(uint8_t* resultBuffer);

    uint8_t get_SNS_CP_HIGH(uint8_t* resultBuffer);
    uint8_t get_SNS_VDD_SHORT(uint8_t* resultBuffer);
    uint8_t get_SNS_GND_SHORT(uint8_t* resultBuffer);
    uint8_t get_SNS_SNS_SHORT(uint8_t* resultBuffer);

    uint8_t get_CMOD_SHIELD_TEST(uint8_t* resultBuffer);

    uint8_t get_BUTTON_STAT(uint8_t* resultBuffer);
    uint8_t get_LATCHED_BUTTON_STAT(uint8_t* resultBuffer);

    uint8_t get_PROX_STAT(uint8_t* resultBuffer);
    uint8_t get_LATCHED_PROX_STAT(uint8_t* resultBuffer);

    uint8_t get_SYNC_COUNTER0(uint8_t* resultBuffer);
    uint8_t get_SYNC_COUNTER1(uint8_t* resultBuffer);
    uint8_t get_SYNC_COUNTER2(uint8_t* resultBuffer);

    uint8_t get_DIFFERENCE_COUNT_SENSOR(uint16_t* resultBuffer);

    uint8_t get_GPO_DATA(uint8_t* resultBuffer);

    uint8_t get_DEBUG_SENSOR_ID(uint8_t* resultBuffer);
    uint8_t get_DEBUG_CP(uint8_t* resultBuffer);
    uint8_t get_DEBUG_DIFFERENCE_COUNT0(uint16_t* resultBuffer);
    uint8_t get_DEBUG_BASELINE0(uint16_t* resultBuffer);
    uint8_t get_DEBUG_RAW_COUNT0(uint16_t* resultBuffer);
    uint8_t get_DEBUG_AVG_RAW_COUNT0(uint16_t* resultBuffer);

    uint8_t setPointer(int registerAddress);
    uint8_t requestData(uint8_t count, uint8_t* resultBuffer);
    uint8_t writeData(uint8_t registerAddress, uint8_t count, uint8_t* data);
    uint8_t requestDataFromAddress(uint8_t registerAddress, uint8_t count, uint8_t* resultBuffer);

    // Comand functions
    uint8_t applyRegister();
    uint8_t calculateCRC();
    uint8_t enterLowPower();
    uint8_t resetIC();
    uint8_t activateSettings();
};
#endif