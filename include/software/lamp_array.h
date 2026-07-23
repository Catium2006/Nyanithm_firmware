/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */

#ifndef __LAMP_ARRAY_H__
#define __LAMP_ARRAY_H__

#include <stdbool.h>
#include <stdint.h>
#include <tusb.h>

// HID instance index used by LampArray node in this firmware.
#define HID_INSTANCE_LAMP_ARRAY 1

// LampArray report IDs.
enum LampArrayReportId {
    LAMP_ARRAY_REPORT_ATTRIBUTES = 0x01,
    LAMP_ARRAY_REPORT_ATTRIBUTES_REQUEST = 0x02,
    LAMP_ARRAY_REPORT_ATTRIBUTES_RESPONSE = 0x03,
    LAMP_ARRAY_REPORT_MULTI_UPDATE = 0x04,
    LAMP_ARRAY_REPORT_RANGE_UPDATE = 0x05,
    LAMP_ARRAY_REPORT_CONTROL = 0x06,
};

void lamp_array_init(void);
void lamp_array_apply(void);

uint16_t lamp_array_get_report(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
void lamp_array_set_report(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

#endif
