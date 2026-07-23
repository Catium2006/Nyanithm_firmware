/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#ifndef __CONTROLLER_CONFIG_H__
#define __CONTROLLER_CONFIG_H__
#include <nyanithm_shared.h>

extern controller_config ControllerConfig;

void readConfig();
void setConfig();
void saveConfig();
bool checkConfigBuf(controller_config* config);
uint8_t getConfigPage();
void eraseConfigSector();

#endif