/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#ifndef __CHUNI_IO_H__
#define __CHUNI_IO_H__

#include <stdint-gcc.h>
#include <nyanithm_shared.h>

void serial_io();

void hid_task_chuni_input();

extern bool game_connected;
extern bool hid_working ;

#endif