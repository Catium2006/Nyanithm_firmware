#ifndef __HW_DEVICES_H__
#define __HW_DEVICES_H__
#include <WS2812.hpp>
#include <cy8cmbr3116.h>
#include <cy8cmbr3116_cfg.h>
#include <gpio_def.h>
#include <mpr121.h>
#include <pca954x.h>
#include <vl53l0x.h>

extern VL53L0X tof0;
extern VL53L0X tof1;
extern VL53L0X tof2;
extern VL53L0X tof3;
extern VL53L0X tof4;

extern MPR121 mpr0;
extern MPR121 mpr1;
extern MPR121 mpr2;

extern CY8CMBR3116 MBR3116A;
extern CY8CMBR3116 MBR3116B;
extern CY8CMBR3116 MBR3116C;

extern PCA954X mux0;

extern WS2812 RGB_LED;

void initHwDevices();
void updateInputState();


void updateTouchData4k();
void updateTouchData6k();

extern int16_t heightData[5];
extern uint16_t heightDataOriginal[5];
extern bool airKeys[6];

extern uint8_t touchData[4];
extern bool touchData4k[4];
extern bool touchData6k[6];

#endif