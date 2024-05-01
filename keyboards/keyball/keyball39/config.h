/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* #include "config_common.h" */

// USB Device descriptor parameters
/* #define VENDOR_ID           0x5957      // "YW" = Yowkees */
/* #define PRODUCT_ID          0x0200 */
/* #define DEVICE_VER          0x0001 */
/* #define MANUFACTURER        Yowkees */
/* #define PRODUCT             Keyball39 */

// Key matrix parameters
#define MATRIX_ROWS         (4 * 2)  // split keyboard
#define MATRIX_COLS         6
#define MATRIX_ROW_PINS     { F4, F5, F6, F7 }
#define MATRIX_COL_PINS     { D4, C6, D7, E6, B4, B5 }
#define MATRIX_MASKED
#define DEBOUNCE            5
#define DIODE_DIRECTION     COL2ROW

// Split parameters
#define SOFT_SERIAL_PIN         D2
#define SPLIT_HAND_MATRIX_GRID  F6, B5
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT
/* #define SPLIT_USB_DETECT */
/* #define SPLIT_USB_TIMEOUT       500 */

#define SPLIT_TRANSACTION_IDS_KB KEYBALL_GET_INFO, KEYBALL_GET_MOTION, KEYBALL_SET_CPI

// RGB LED settings
#define WS2812_DI_PIN          D3
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM      48
#    define RGBLED_SPLIT    { 24, 24 }  // (24 + 22)
// clang-format off
#    define LED_LAYOUT( \
        L00,  L01,  L02,  L03,  L04,              R04,  R03,  R02,  R01,  R00, \
        L10,  L11,  L12,  L13,  L14,              R14,  R13,  R12,  R11,  R10, \
        L20,  L21,  L22,  L23,  L24,              R24,  R23,  R22,  R21,  R20, \
        L30,  L31,  L32,                                                  R30, \
       UL00,       UL01,                                     UR01,       UR00, \
       UL10,  UL11,      UL12, UL13,       UR13, UR12,       UR11,       UR10) \
       { \
       L04, L14, L24, \
       L03, L13, L23, \
       L02, L12, L22, L32, \
       L01, L11, L21, L31, \
       L00, L10, L20, L30, \
       UL01, UL00, UL10, UL11, UL12, UL13, \
       \
       UR13, UR12, UR11, UR10, UR00, UR01, \
       R00, R10, R20, R30, \
       R01, R11, R21, \
       R02, R12, R22, \
       R03, R13, R23, \
       R04, R14, R24 }
#    define RGBLIGHT_LED_MAP LED_LAYOUT( \
        0,  1,  2,  3,  4,     24, 25, 26, 27, 28, \
        5,  6,  7,  8,  9,     29, 30, 31, 32, 33, \
       10, 11, 12, 13, 14,     34, 35, 36, 37, 38, \
       15, 16, 17,                             39, \
       18,     19,                 40,         41, \
       19, 21,     22, 23,     42, 43,     44, 45  \
       )
// clang-format on
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL  150 // limitated for power consumption
#    endif
#    ifndef RGBLIGHT_VAL_STEP
#        define RGBLIGHT_VAL_STEP   15
#    endif
#    ifndef RGBLIGHT_HUE_STEP
#        define RGBLIGHT_HUE_STEP   17
#    endif
#    ifndef RGBLIGHT_SAT_STEP
#        define RGBLIGHT_SAT_STEP   17
#    endif
#endif
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_SPLIT    { 24, 24 }
#endif

#ifndef OLED_FONT_H
#    define OLED_FONT_H "keyboards/keyball/lib/glcdfont.c"
#endif

#if !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_8BIT
#endif

// To squeeze firmware size
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
/* #define NO_ACTION_MACRO */
/* #define NO_ACTION_FUNCTION */
