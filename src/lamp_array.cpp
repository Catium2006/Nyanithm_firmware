/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2026 Catium2006
 */



#include <lamp_array.h>

#include <controller_config.h>
#include <hw_devices.h>
#include <string.h>

#include <serial_io.h>

static constexpr uint16_t kLampCount = 31;
static constexpr uint8_t kMaxMultiUpdateLamps = 8;

// Static device geometry used for standard LampArray attributes.
static constexpr uint32_t kBoundingBoxWidthUm = 31000;
static constexpr uint32_t kBoundingBoxHeightUm = 1000;
static constexpr uint32_t kBoundingBoxDepthUm = 1000;
static constexpr uint32_t kLampArrayKind = 0;           // Device-specific/undefined kind.
static constexpr uint32_t kMinUpdateIntervalUs = 2000;  // 2ms update cadence.

static constexpr uint32_t kLampUpdateLatencyUs = 2000;
static constexpr uint32_t kLampPurposes = 0;
static constexpr uint8_t kLevelCount = 255;
static constexpr uint8_t kIsProgrammable = 1;
static constexpr uint8_t kInputBinding = 0;

static uint16_t s_selected_lamp = 0;
static bool s_autonomous_mode = false;
static bool s_dirty = false;
static uint8_t s_rgb[kLampCount][3];

static uint16_t clamp_lamp_id(uint16_t lamp_id) {
    return lamp_id < kLampCount ? lamp_id : (kLampCount - 1);
}

static uint16_t read_le16(uint8_t const* src) {
    return (uint16_t)(src[0] | ((uint16_t)src[1] << 8));
}

static void write_le16(uint8_t* dst, uint16_t value) {
    dst[0] = (uint8_t)(value & 0xFF);
    dst[1] = (uint8_t)((value >> 8) & 0xFF);
}

static void write_le32(uint8_t* dst, uint32_t value) {
    dst[0] = (uint8_t)(value & 0xFF);
    dst[1] = (uint8_t)((value >> 8) & 0xFF);
    dst[2] = (uint8_t)((value >> 16) & 0xFF);
    dst[3] = (uint8_t)((value >> 24) & 0xFF);
}

static uint32_t scale_channel(uint8_t c, uint8_t intensity) {
    return ((uint32_t)c * (uint32_t)intensity) / 255;
}

static void set_lamp_rgb(uint16_t lamp_id, uint8_t r, uint8_t g, uint8_t b, uint8_t intensity) {
    lamp_id = clamp_lamp_id(lamp_id);
    s_rgb[lamp_id][0] = (uint8_t)scale_channel(r, intensity);
    s_rgb[lamp_id][1] = (uint8_t)scale_channel(g, intensity);
    s_rgb[lamp_id][2] = (uint8_t)scale_channel(b, intensity);
    s_dirty = true;
}

void lamp_array_init(void) {
    memset(s_rgb, 0x00, sizeof(s_rgb));
    s_selected_lamp = 0;
    s_autonomous_mode = false;
    s_dirty = true;
}

void lamp_array_apply(void) {
    if (game_connected) {
        return;
    }
    if(!(ControllerConfig.cfg0 & CFG0_BIT_ENABLE_LAMPARRAY)){
        return;
    }
    if (!s_dirty) {
        return;
    }

    for (uint8_t i = 0; i < kLampCount; i++) {
        uint8_t r = s_rgb[i][0];
        uint8_t g = s_rgb[i][1];
        uint8_t b = s_rgb[i][2];

        uint32_t R = (r * ControllerConfig.lightLimit) / 255;
        uint32_t G = (g * ControllerConfig.lightLimit) / 255;
        uint32_t B = (b * ControllerConfig.lightLimit) / 255;
        r = (uint8_t)R;
        g = (uint8_t)G;
        b = (uint8_t)B;

        if ((i & 1) && (ControllerConfig.cfg0 & CFG0_BIT_DARKER_GAP)) {
            r >>= 2;
            g >>= 2;
            b >>= 2;
        }

        // Keep physical LED indexing consistent with existing firmware mapping.
        led_controller.setColor(30 - i, r, g, b);
    }
    led_controller.flush();
    s_dirty = false;
}

static uint16_t build_attributes_report(uint8_t* buffer, uint16_t reqlen) {
    // Layout: 2 + 5*4 = 22 bytes
    uint8_t report[22];
    memset(report, 0x00, sizeof(report));
    write_le16(report + 0, kLampCount);
    write_le32(report + 2, kBoundingBoxWidthUm);
    write_le32(report + 6, kBoundingBoxHeightUm);
    write_le32(report + 10, kBoundingBoxDepthUm);
    write_le32(report + 14, kLampArrayKind);
    write_le32(report + 18, kMinUpdateIntervalUs);

    uint16_t n = reqlen < sizeof(report) ? reqlen : (uint16_t)sizeof(report);
    memcpy(buffer, report, n);
    return n;
}

static uint16_t build_lamp_attributes_response(uint8_t* buffer, uint16_t reqlen) {
    // Layout: 2 + 5*4 + 6*1 = 28 bytes
    uint8_t report[28];
    memset(report, 0x00, sizeof(report));

    uint16_t lamp_id = clamp_lamp_id(s_selected_lamp);
    write_le16(report + 0, lamp_id);

    // Position: distribute lamps linearly along X axis.
    uint32_t x = (lamp_id * kBoundingBoxWidthUm) / (kLampCount - 1);
    write_le32(report + 2, x);
    write_le32(report + 6, 0);
    write_le32(report + 10, 0);
    write_le32(report + 14, kLampUpdateLatencyUs);
    write_le32(report + 18, kLampPurposes);

    report[22] = kLevelCount;      // RedLevelCount
    report[23] = kLevelCount;      // GreenLevelCount
    report[24] = kLevelCount;      // BlueLevelCount
    report[25] = kLevelCount;      // IntensityLevelCount
    report[26] = kIsProgrammable;  // IsProgrammable
    report[27] = kInputBinding;    // InputBinding

    uint16_t n = reqlen < sizeof(report) ? reqlen : (uint16_t)sizeof(report);
    memcpy(buffer, report, n);
    return n;
}

uint16_t lamp_array_get_report(uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    if (!buffer || reqlen == 0) {
        return 0;
    }
    if (report_type != HID_REPORT_TYPE_FEATURE) {
        return 0;
    }

    if (report_id == LAMP_ARRAY_REPORT_ATTRIBUTES) {
        return build_attributes_report(buffer, reqlen);
    }

    if (report_id == LAMP_ARRAY_REPORT_ATTRIBUTES_REQUEST) {
        if (reqlen < 2) {
            return 0;
        }
        write_le16(buffer, s_selected_lamp);
        return 2;
    }

    if (report_id == LAMP_ARRAY_REPORT_ATTRIBUTES_RESPONSE) {
        return build_lamp_attributes_response(buffer, reqlen);
    }

    if (report_id == LAMP_ARRAY_REPORT_CONTROL) {
        buffer[0] = s_autonomous_mode ? 1 : 0;
        return 1;
    }

    if (report_id == LAMP_ARRAY_REPORT_MULTI_UPDATE) {
        // Return an all-zero template (count=0) to keep GET_FEATURE probes from stalling.
        const uint16_t kLen = 50;
        uint16_t n = reqlen < kLen ? reqlen : kLen;
        memset(buffer, 0x00, n);
        return n;
    }

    if (report_id == LAMP_ARRAY_REPORT_RANGE_UPDATE) {
        // Return an all-zero template to keep GET_FEATURE probes from stalling.
        const uint16_t kLen = 9;
        uint16_t n = reqlen < kLen ? reqlen : kLen;
        memset(buffer, 0x00, n);
        return n;
    }

    return 0;
}

static void handle_multi_update(uint8_t const* buffer, uint16_t bufsize) {
    // Layout: [count:1][flags:1][lamp_id:16 bytes][channels:32 bytes]
    // channels are 8 groups of RGBI.
    if (bufsize < 50 || s_autonomous_mode) {
        return;
    }

    uint8_t count = buffer[0];
    if (count > kMaxMultiUpdateLamps) {
        count = kMaxMultiUpdateLamps;
    }

    const uint8_t* lamp_ids = buffer + 2;
    const uint8_t* channels = buffer + 18;

    for (uint8_t i = 0; i < count; i++) {
        uint16_t lamp_id = read_le16(lamp_ids + (i * 2));
        uint8_t r = channels[i * 4 + 0];
        uint8_t g = channels[i * 4 + 1];
        uint8_t b = channels[i * 4 + 2];
        uint8_t intensity = channels[i * 4 + 3];
        set_lamp_rgb(lamp_id, r, g, b, intensity);
    }
    lamp_array_apply();
}

static void handle_range_update(uint8_t const* buffer, uint16_t bufsize) {
    // Layout: [flags:1][start:2][end:2][r][g][b][i]
    if (bufsize < 9 || s_autonomous_mode) {
        return;
    }

    uint16_t start = clamp_lamp_id(read_le16(buffer + 1));
    uint16_t end = clamp_lamp_id(read_le16(buffer + 3));
    if (end < start) {
        uint16_t tmp = start;
        start = end;
        end = tmp;
    }

    uint8_t r = buffer[5];
    uint8_t g = buffer[6];
    uint8_t b = buffer[7];
    uint8_t intensity = buffer[8];

    for (uint16_t id = start; id <= end; id++) {
        set_lamp_rgb(id, r, g, b, intensity);
    }
    lamp_array_apply();
}

void lamp_array_set_report(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    if (!buffer || bufsize == 0) {
        return;
    }
    if (report_type != HID_REPORT_TYPE_FEATURE) {
        return;
    }

    if (report_id == LAMP_ARRAY_REPORT_ATTRIBUTES_REQUEST) {
        if (bufsize >= 2) {
            s_selected_lamp = clamp_lamp_id(read_le16(buffer));
        }
        return;
    }

    if (report_id == LAMP_ARRAY_REPORT_MULTI_UPDATE) {
        handle_multi_update(buffer, bufsize);
        return;
    }

    if (report_id == LAMP_ARRAY_REPORT_RANGE_UPDATE) {
        handle_range_update(buffer, bufsize);
        return;
    }

    if (report_id == LAMP_ARRAY_REPORT_CONTROL) {
        s_autonomous_mode = (buffer[0] & 0x01) != 0;
        return;
    }
}
