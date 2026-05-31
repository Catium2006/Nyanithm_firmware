/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "bsp/board_api.h"
#include "tusb.h"

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]         HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n) ((CFG_TUD_##itf) << (n))
#define USB_PID (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4))

#define USB_VID 0xCafe
#define USB_BCD 0x0200

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device = { .bLength = sizeof(tusb_desc_device_t),
                                         .bDescriptorType = TUSB_DESC_DEVICE,
                                         .bcdUSB = USB_BCD,

                                         // Use Interface Association Descriptor (IAD) for CDC
                                         // As required by USB Specs IAD's subclass must be common class (2) and protocol must be IAD (1)
                                         .bDeviceClass = TUSB_CLASS_MISC,
                                         .bDeviceSubClass = MISC_SUBCLASS_COMMON,
                                         .bDeviceProtocol = MISC_PROTOCOL_IAD,
                                         .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

                                         .idVendor = USB_VID,
                                         .idProduct = USB_PID,
                                         .bcdDevice = 0x0100,

                                         .iManufacturer = 0x01,
                                         .iProduct = 0x02,
                                         .iSerialNumber = 0x03,

                                         .bNumConfigurations = 0x01 };

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const* tud_descriptor_device_cb(void) {
    return (uint8_t const*)&desc_device;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+
enum { ITF_NUM_HID_KBD = 0, ITF_NUM_HID_LAMP, ITF_NUM_CDC_0, ITF_NUM_CDC_0_DATA, ITF_NUM_TOTAL };

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + CFG_TUD_HID * TUD_HID_DESC_LEN + CFG_TUD_CDC * TUD_CDC_DESC_LEN)

#if CFG_TUSB_MCU == OPT_MCU_LPC175X_6X || CFG_TUSB_MCU == OPT_MCU_LPC177X_8X || CFG_TUSB_MCU == OPT_MCU_LPC40XX
// LPC 17xx and 40xx endpoint type (bulk/interrupt/iso) are fixed by its number
// 0 control, 1 In, 2 Bulk, 3 Iso, 4 In etc ...
#define EPNUM_CDC_0_NOTIF 0x81
#define EPNUM_CDC_0_OUT 0x02
#define EPNUM_CDC_0_IN 0x82

#elif CFG_TUSB_MCU == OPT_MCU_CXD56
// CXD56 USB driver has fixed endpoint type (bulk/interrupt/iso) and direction (IN/OUT) by its number
// 0 control (IN/OUT), 1 Bulk (IN), 2 Bulk (OUT), 3 In (IN), 4 Bulk (IN), 5 Bulk (OUT), 6 In (IN)
#define EPNUM_CDC_0_NOTIF 0x83
#define EPNUM_CDC_0_OUT 0x02
#define EPNUM_CDC_0_IN 0x81

#elif defined(TUD_ENDPOINT_ONE_DIRECTION_ONLY)
// MCUs that don't support a same endpoint number with different direction IN and OUT defined in tusb_mcu.h
//    e.g EP1 OUT & EP1 IN cannot exist together
#define EPNUM_CDC_0_NOTIF 0x81
#define EPNUM_CDC_0_OUT 0x02
#define EPNUM_CDC_0_IN 0x83

#else
#define EPNUM_HID_KBD 0x81
#define EPNUM_HID_LAMP 0x84
#define EPNUM_CDC_0_NOTIF 0x82
#define EPNUM_CDC_0_OUT 0x02
#define EPNUM_CDC_0_IN 0x83

#endif

// HID #0: keyboard report
uint8_t const desc_hid_report_keyboard[] = {
    0x05, 0x01,  // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,  // USAGE (Keyboard)
    0xa1, 0x01,  // COLLECTION (Application)
    0x05, 0x07,  //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,  //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,  //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,  //   LOGICAL_MINIMUM (0)
    0x25, 0x01,  //   LOGICAL_MAXIMUM (1)
    0x95, 0x08,  //   REPORT_COUNT (8)
    0x75, 0x01,  //   REPORT_SIZE (1)
    0x81, 0x02,  //   INPUT (Data,Var,Abs)
    0x95, 0x01,  //   REPORT_COUNT (1)
    0x75, 0x08,  //   REPORT_SIZE (8)
    0x81, 0x03,  //   INPUT (Cnst,Var,Abs)
    0x05, 0x07,  //   USAGE_PAGE (Keyboard)
    0x19, 0x04,  //   USAGE_MINIMUM (Keyboard a and A)
    0x29, 0x65,  //   USAGE_MAXIMUM (Keyboard Application)
    0x15, 0x00,  //   LOGICAL_MINIMUM (0)
    0x25, 0x01,  //   LOGICAL_MAXIMUM (1)
    0x95, 0x62,  //   REPORT_COUNT (98)
    0x75, 0x01,  //   REPORT_SIZE (1)
    0x81, 0x02,  //   INPUT (Data,Var,Abs)
    0x95, 0x01,  //   REPORT_COUNT (1)
    0x75, 0x06,  //   REPORT_SIZE (6)
    0x81, 0x03,  //   INPUT (Cnst,Var,Abs)
    0x05, 0x08,  //   USAGE_PAGE (LEDs)
    0x19, 0x01,  //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,  //   USAGE_MAXIMUM (Kana)
    0x15, 0x00,  //   LOGICAL_MINIMUM (0)
    0x25, 0x01,  //   LOGICAL_MAXIMUM (1)
    0x95, 0x05,  //   REPORT_COUNT (5)
    0x75, 0x01,  //   REPORT_SIZE (1)
    0x91, 0x02,  //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,  //   REPORT_COUNT (1)
    0x75, 0x03,  //   REPORT_SIZE (3)
    0x91, 0x03,  //   OUTPUT (Cnst,Var,Abs)
    0xc0         // END_COLLECTION
};

// HID #1: LampArray report
// Descriptor aligned to HID Lighting and Illumination standard usage model.
uint8_t const desc_hid_report_lamp[] = {
    0x06, 0x59, 0x00,  // USAGE_PAGE (Lighting and Illumination)
    0x09, 0x01,        // USAGE (LampArray)
    0xA1, 0x01,        // COLLECTION (Application)

    // Feature report #1: LampArrayAttributesReport
    0x85, 0x01,        //   REPORT_ID (1)
    0x09, 0x02,        //   USAGE (LampArrayAttributesReport)
    0xA1, 0x02,        //   COLLECTION (Logical)
    0x09, 0x03,        //     USAGE (LampCount)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  // LOGICAL_MAXIMUM (65535)
    0x75, 0x10,        //     REPORT_SIZE (16)
    0x95, 0x01,        //     REPORT_COUNT (1)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0x09, 0x04,        //     USAGE (BoundingBoxWidthInMicrometers)
    0x09, 0x05,        //     USAGE (BoundingBoxHeightInMicrometers)
    0x09, 0x06,        //     USAGE (BoundingBoxDepthInMicrometers)
    0x09, 0x07,        //     USAGE (LampArrayKind)
    0x09, 0x08,        //     USAGE (MinUpdateIntervalInMicroseconds)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0xFF, 0x7F,  // LOGICAL_MAXIMUM (2147483647)
    0x75, 0x20,        //     REPORT_SIZE (32)
    0x95, 0x05,        //     REPORT_COUNT (5)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0xC0,              //   END_COLLECTION

    // Feature report #2: LampAttributesRequestReport
    0x85, 0x02,        //   REPORT_ID (2)
    0x09, 0x20,        //   USAGE (LampAttributesRequestReport)
    0xA1, 0x02,        //   COLLECTION (Logical)
    0x09, 0x21,        //     USAGE (LampId)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  // LOGICAL_MAXIMUM (65535)
    0x75, 0x10,        //     REPORT_SIZE (16)
    0x95, 0x01,        //     REPORT_COUNT (1)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0xC0,              //   END_COLLECTION

    // Feature report #3: LampAttributesResponseReport
    0x85, 0x03,        //   REPORT_ID (3)
    0x09, 0x22,        //   USAGE (LampAttributesResponseReport)
    0xA1, 0x02,        //   COLLECTION (Logical)
    0x09, 0x21,        //     USAGE (LampId)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  // LOGICAL_MAXIMUM (65535)
    0x75, 0x10,        //     REPORT_SIZE (16)
    0x95, 0x01,        //     REPORT_COUNT (1)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0x09, 0x23,        //     USAGE (PositionXInMicrometers)
    0x09, 0x24,        //     USAGE (PositionYInMicrometers)
    0x09, 0x25,        //     USAGE (PositionZInMicrometers)
    0x09, 0x27,        //     USAGE (UpdateLatencyInMicroseconds)
    0x09, 0x26,        //     USAGE (LampPurposes)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0xFF, 0x7F,  // LOGICAL_MAXIMUM (2147483647)
    0x75, 0x20,        //     REPORT_SIZE (32)
    0x95, 0x05,        //     REPORT_COUNT (5)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0x09, 0x28,        //     USAGE (RedLevelCount)
    0x09, 0x29,        //     USAGE (GreenLevelCount)
    0x09, 0x2A,        //     USAGE (BlueLevelCount)
    0x09, 0x2B,        //     USAGE (IntensityLevelCount)
    0x09, 0x2C,        //     USAGE (IsProgrammable)
    0x09, 0x2D,        //     USAGE (InputBinding)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x00,  // LOGICAL_MAXIMUM (255)
    0x75, 0x08,        //     REPORT_SIZE (8)
    0x95, 0x06,        //     REPORT_COUNT (6)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0xC0,              //   END_COLLECTION

    // Feature report #4: LampMultiUpdateReport
    0x85, 0x04,        //   REPORT_ID (4)
    0x09, 0x50,        //   USAGE (LampMultiUpdateReport)
    0xA1, 0x02,        //   COLLECTION (Logical)
    0x09, 0x03,        //     USAGE (LampCount)
    0x09, 0x55,        //     USAGE (LampUpdateFlags)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x25, 0x08,        //     LOGICAL_MAXIMUM (8)
    0x75, 0x08,        //     REPORT_SIZE (8)
    0x95, 0x02,        //     REPORT_COUNT (2)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0x09, 0x21,        //     USAGE (LampId)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  // LOGICAL_MAXIMUM (65535)
    0x75, 0x10,        //     REPORT_SIZE (16)
    0x95, 0x08,        //     REPORT_COUNT (8)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    // 8x RGBI channels
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x00,  // LOGICAL_MAXIMUM (255)
    0x75, 0x08,        //     REPORT_SIZE (8)
    0x95, 0x20,        //     REPORT_COUNT (32)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0xC0,              //   END_COLLECTION

    // Feature report #5: LampRangeUpdateReport
    0x85, 0x05,        //   REPORT_ID (5)
    0x09, 0x60,        //   USAGE (LampRangeUpdateReport)
    0xA1, 0x02,        //   COLLECTION (Logical)
    0x09, 0x55,        //     USAGE (LampUpdateFlags)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x25, 0x08,        //     LOGICAL_MAXIMUM (8)
    0x75, 0x08,        //     REPORT_SIZE (8)
    0x95, 0x01,        //     REPORT_COUNT (1)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0x09, 0x61,        //     USAGE (LampIdStart)
    0x09, 0x62,        //     USAGE (LampIdEnd)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  // LOGICAL_MAXIMUM (65535)
    0x75, 0x10,        //     REPORT_SIZE (16)
    0x95, 0x02,        //     REPORT_COUNT (2)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0x09, 0x51,        //     USAGE (RedUpdateChannel)
    0x09, 0x52,        //     USAGE (GreenUpdateChannel)
    0x09, 0x53,        //     USAGE (BlueUpdateChannel)
    0x09, 0x54,        //     USAGE (IntensityUpdateChannel)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x00,  // LOGICAL_MAXIMUM (255)
    0x75, 0x08,        //     REPORT_SIZE (8)
    0x95, 0x04,        //     REPORT_COUNT (4)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0xC0,              //   END_COLLECTION

    // Feature report #6: LampArrayControlReport
    0x85, 0x06,        //   REPORT_ID (6)
    0x09, 0x70,        //   USAGE (LampArrayControlReport)
    0xA1, 0x02,        //   COLLECTION (Logical)
    0x09, 0x71,        //     USAGE (AutonomousMode)
    0x15, 0x00,        //     LOGICAL_MINIMUM (0)
    0x25, 0x01,        //     LOGICAL_MAXIMUM (1)
    0x75, 0x08,        //     REPORT_SIZE (8)
    0x95, 0x01,        //     REPORT_COUNT (1)
    0xB1, 0x02,        //     FEATURE (Data,Var,Abs)
    0xC0,              //   END_COLLECTION

    0xC0               // END_COLLECTION
};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const* tud_hid_descriptor_report_cb(uint8_t itf) {
    if (itf == 0) {
        return desc_hid_report_keyboard;
    }
    if (itf == 1) {
        return desc_hid_report_lamp;
    }

    return NULL;
}

uint8_t const desc_fs_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

    // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
    TUD_HID_DESCRIPTOR(ITF_NUM_HID_KBD, 4, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report_keyboard), EPNUM_HID_KBD, CFG_TUD_HID_EP_BUFSIZE, 5),
    TUD_HID_DESCRIPTOR(ITF_NUM_HID_LAMP, 5, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report_lamp), EPNUM_HID_LAMP, CFG_TUD_HID_EP_BUFSIZE, 5),

    // 1st CDC: Interface number, string index, EP notification address and size, EP data address (out, in) and size.
    TUD_CDC_DESCRIPTOR(ITF_NUM_CDC_0, 0, EPNUM_CDC_0_NOTIF, 8, EPNUM_CDC_0_OUT, EPNUM_CDC_0_IN, 64),
};

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const* tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;  // for multiple configurations

    return desc_fs_configuration;
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// String Descriptor Index
enum { STRID_LANGID = 0, STRID_MANUFACTURER, STRID_PRODUCT, STRID_SERIAL, STRID_HID_KBD_INTERFACE, STRID_HID_LAMP_INTERFACE, STRID_CDC_INTERFACE };

// array of pointer to string descriptors
char const* string_desc_arr[] = {
    (const char[]){ 0x09, 0x04 },  // 0: 英语 (0x0409)
    "NyaLab",                      // 1: 厂商名
    "Nyanithm Controller",          // 2: 产品名
    NULL,                          // 3: 序列号（自动生成）
    "Nyanithm HID Keyboard",        // 4: HID键盘接口
    "Nyanithm HID LampArray",       // 5: HID灯阵接口
    "Nyanithm CDC",                 // 6: CDC接口
};

static uint16_t _desc_str[32 + 1];

static void ascii_to_utf16le(uint16_t* dest, const char* src, size_t max_chars) {
    size_t i = 0;
    while (i < max_chars && src[i] != '\0') {
        dest[i] = (uint16_t)src[i] & 0xFF;
        i++;
    }
    for (; i < max_chars; i++) {
        dest[i] = 0;
    }
}

// Invoked when received GET STRING DESCRIPTOR request
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void)langid;
    size_t chr_count = 0;
    memset(_desc_str, 0, sizeof(_desc_str));

    switch (index) {
    case STRID_LANGID:
        // 语言ID描述符：0x0409 (英语-美国)，固定长度2字节
        _desc_str[0] = (TUSB_DESC_STRING << 8) | 4;  // 长度=4 (2字节头 + 2字节数据)
        _desc_str[1] = 0x0409;                       // UTF-16LE的0x0409（小端序：09 04）
        return _desc_str;

    case STRID_MANUFACTURER:
        chr_count = strlen(string_desc_arr[1]);
        ascii_to_utf16le(_desc_str + 1, string_desc_arr[1], 32);
        break;

    case STRID_PRODUCT:
        chr_count = strlen(string_desc_arr[2]);
        ascii_to_utf16le(_desc_str + 1, string_desc_arr[2], 32);
        break;

    case STRID_SERIAL:
        chr_count = board_usb_get_serial(_desc_str + 1, 32);
        if (chr_count == 0) {
            ascii_to_utf16le(_desc_str + 1, "0123456789ABCDEF", 32);
            chr_count = strlen("0123456789ABCDEF");
        }
        break;

    case STRID_HID_KBD_INTERFACE:
        chr_count = strlen(string_desc_arr[4]);
        ascii_to_utf16le(_desc_str + 1, string_desc_arr[4], 32);
        break;

    case STRID_HID_LAMP_INTERFACE:
        chr_count = strlen(string_desc_arr[5]);
        ascii_to_utf16le(_desc_str + 1, string_desc_arr[5], 32);
        break;

    case STRID_CDC_INTERFACE:
        chr_count = strlen(string_desc_arr[6]);
        ascii_to_utf16le(_desc_str + 1, string_desc_arr[6], 32);
        break;

    default:
        return NULL;
    }

    chr_count = (chr_count > 32) ? 32 : chr_count;

    _desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));
    return _desc_str;
}
