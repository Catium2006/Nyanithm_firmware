#ifndef __PRODUCTION_MODE_H__
#define __PRODUCTION_MODE_H__

#include <boot_mode.h>

void productionMode();

void program_cy8cmbr3116_custom(uint8_t addr, uint8_t* cfg);

bool detect3116(uint8_t addr);

#endif