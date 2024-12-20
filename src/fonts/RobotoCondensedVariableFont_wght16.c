/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: --bpp 4 --size 16 --no-compress --font RobotoCondensed-VariableFont_wght.ttf --range 32-127 --format lvgl -o RobotoCondensedVariableFont_wght16.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTOCONDENSEDVARIABLEFONT_WGHT16
#define ROBOTOCONDENSEDVARIABLEFONT_WGHT16 1
#endif

#if ROBOTOCONDENSEDVARIABLEFONT_WGHT16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xbb, 0xba, 0xba, 0xba, 0xba, 0xaa, 0xaa, 0xa9,
    0x55, 0x0, 0x66, 0x99,

    /* U+0022 "\"" */
    0xe2, 0xd4, 0xe2, 0xd3, 0xe0, 0xd2, 0xe0, 0xd1,
    0x0, 0x0,

    /* U+0023 "#" */
    0x0, 0x2e, 0x8, 0x80, 0x0, 0x5b, 0xa, 0x60,
    0x0, 0x79, 0xd, 0x30, 0x7f, 0xff, 0xff, 0xf5,
    0x12, 0xf6, 0x4f, 0x20, 0x0, 0xf1, 0x4c, 0x0,
    0x1, 0xf0, 0x79, 0x0, 0xff, 0xff, 0xff, 0xd0,
    0x29, 0xc2, 0xe7, 0x20, 0x9, 0x70, 0xe2, 0x0,
    0xb, 0x51, 0xf0, 0x0, 0xe, 0x23, 0xd0, 0x0,

    /* U+0024 "$" */
    0x0, 0x7, 0xa0, 0x0, 0x0, 0x7, 0xa0, 0x0,
    0x0, 0x8f, 0xf8, 0x0, 0x5, 0xf8, 0x7f, 0x70,
    0xa, 0xb0, 0xa, 0xc0, 0xb, 0xb0, 0x5, 0xa0,
    0x8, 0xf3, 0x0, 0x0, 0x1, 0xdf, 0x91, 0x0,
    0x0, 0x6, 0xef, 0x30, 0x0, 0x0, 0xd, 0xd0,
    0x1a, 0x20, 0x6, 0xf0, 0xf, 0x70, 0x7, 0xf0,
    0xa, 0xe6, 0x7f, 0xa0, 0x0, 0x9f, 0xfa, 0x0,
    0x0, 0x9, 0x80, 0x0, 0x0, 0x4, 0x40, 0x0,

    /* U+0025 "%" */
    0x6, 0xfd, 0x20, 0x0, 0x0, 0xf, 0x27, 0xa0,
    0x15, 0x0, 0x2d, 0x3, 0xd0, 0x96, 0x0, 0xf,
    0x27, 0xa2, 0xd0, 0x0, 0x5, 0xed, 0x2a, 0x60,
    0x0, 0x0, 0x0, 0x2d, 0x0, 0x0, 0x0, 0x0,
    0xa6, 0xaf, 0x80, 0x0, 0x3, 0xd5, 0xc1, 0xd2,
    0x0, 0xb, 0x58, 0x70, 0x96, 0x0, 0x3d, 0x8,
    0x70, 0x96, 0x0, 0x55, 0x5, 0xb1, 0xd2, 0x0,
    0x0, 0x0, 0xaf, 0x80,

    /* U+0026 "&" */
    0x0, 0x7e, 0xe6, 0x0, 0x0, 0x3f, 0x86, 0xf2,
    0x0, 0x6, 0xf0, 0xe, 0x50, 0x0, 0x5f, 0x13,
    0xf3, 0x0, 0x0, 0xec, 0xe9, 0x0, 0x0, 0xa,
    0xfd, 0x0, 0x0, 0x4, 0xff, 0xd0, 0x27, 0x0,
    0xe9, 0x1f, 0x96, 0xe0, 0x2f, 0x30, 0x6f, 0xdb,
    0x1, 0xf5, 0x0, 0xdf, 0x50, 0xb, 0xd2, 0x3e,
    0xf9, 0x0, 0x1a, 0xfe, 0x97, 0xf3,

    /* U+0027 "'" */
    0x2f, 0x2f, 0x2e, 0x2c,

    /* U+0028 "(" */
    0x0, 0x1, 0x0, 0x97, 0x4, 0xd0, 0xc, 0x60,
    0x3f, 0x10, 0x8c, 0x0, 0xb9, 0x0, 0xe7, 0x0,
    0xf6, 0x0, 0xf6, 0x0, 0xe7, 0x0, 0xc8, 0x0,
    0x9b, 0x0, 0x5e, 0x0, 0xf, 0x30, 0x8, 0xa0,
    0x0, 0xd4, 0x0, 0x25,

    /* U+0029 ")" */
    0x10, 0x0, 0x7, 0x90, 0x0, 0xd, 0x40, 0x0,
    0x6d, 0x0, 0x0, 0xf3, 0x0, 0xc, 0x80, 0x0,
    0x9c, 0x0, 0x7, 0xe0, 0x0, 0x6f, 0x0, 0x5,
    0xf0, 0x0, 0x6f, 0x0, 0x7, 0xd0, 0x0, 0xaa,
    0x0, 0xe, 0x60, 0x3, 0xf0, 0x0, 0xa8, 0x0,
    0x3d, 0x0, 0x5, 0x20, 0x0,

    /* U+002A "*" */
    0x0, 0x1f, 0x0, 0x0, 0x1, 0xf0, 0x0, 0x9b,
    0x6f, 0x5b, 0x73, 0x8e, 0xfe, 0x93, 0x0, 0xde,
    0xa0, 0x0, 0x8d, 0x1e, 0x50, 0x7, 0x30, 0x66,
    0x0,

    /* U+002B "+" */
    0x0, 0x8, 0x70, 0x0, 0x0, 0xb, 0xa0, 0x0,
    0x0, 0xb, 0xa0, 0x0, 0x2, 0x2d, 0xc2, 0x20,
    0x5f, 0xff, 0xff, 0xf3, 0x14, 0x4f, 0xf4, 0x41,
    0x0, 0xb, 0xa0, 0x0, 0x0, 0xb, 0xa0, 0x0,
    0x0, 0xb, 0xa0, 0x0, 0x0, 0x3, 0x30, 0x0,

    /* U+002C "," */
    0xf, 0x60, 0xf6, 0x3f, 0x28, 0x90, 0x0, 0x0,

    /* U+002D "-" */
    0x0, 0x0, 0xaf, 0xf9, 0x23, 0x31,

    /* U+002E "." */
    0x88, 0xab,

    /* U+002F "/" */
    0x0, 0x0, 0xe4, 0x0, 0x3, 0xe0, 0x0, 0x8,
    0xa0, 0x0, 0xd, 0x50, 0x0, 0x2f, 0x0, 0x0,
    0x7b, 0x0, 0x0, 0xc6, 0x0, 0x1, 0xf1, 0x0,
    0x5, 0xc0, 0x0, 0xa, 0x70, 0x0, 0xf, 0x20,
    0x0, 0x4e, 0x0, 0x0, 0x99, 0x0, 0x0,

    /* U+0030 "0" */
    0x0, 0x9e, 0xe7, 0x0, 0x7f, 0x56, 0xf5, 0xd,
    0x80, 0xa, 0xb0, 0xf5, 0x0, 0x7e, 0x1f, 0x40,
    0x6, 0xf1, 0xf4, 0x0, 0x6f, 0x1f, 0x40, 0x6,
    0xf1, 0xf4, 0x0, 0x6f, 0xf, 0x60, 0x7, 0xe0,
    0xc9, 0x0, 0xbb, 0x6, 0xf6, 0x7f, 0x50, 0x8,
    0xee, 0x80,

    /* U+0031 "1" */
    0x0, 0x6d, 0x6, 0xef, 0xf0, 0x97, 0x6f, 0x0,
    0x5, 0xf0, 0x0, 0x5f, 0x0, 0x5, 0xf0, 0x0,
    0x5f, 0x0, 0x5, 0xf0, 0x0, 0x5f, 0x0, 0x5,
    0xf0, 0x0, 0x5f, 0x0, 0x5, 0xf0,

    /* U+0032 "2" */
    0x1, 0xaf, 0xe8, 0x0, 0xb, 0xe5, 0x6f, 0x70,
    0x1f, 0x50, 0xb, 0xc0, 0x2a, 0x10, 0x9, 0xc0,
    0x0, 0x0, 0xc, 0x90, 0x0, 0x0, 0x3f, 0x30,
    0x0, 0x0, 0xda, 0x0, 0x0, 0x9, 0xe1, 0x0,
    0x0, 0x5f, 0x30, 0x0, 0x1, 0xe7, 0x0, 0x0,
    0xc, 0xe3, 0x33, 0x31, 0x1f, 0xff, 0xff, 0xf4,

    /* U+0033 "3" */
    0x1, 0xbf, 0xe8, 0x0, 0xcd, 0x57, 0xf5, 0x1f,
    0x40, 0xc, 0xa0, 0x0, 0x0, 0xba, 0x0, 0x2,
    0x6f, 0x40, 0x7, 0xff, 0xa0, 0x0, 0x2, 0x6f,
    0x50, 0x0, 0x0, 0xab, 0x16, 0x10, 0x9, 0xd1,
    0xf5, 0x0, 0xbb, 0xb, 0xd4, 0x7f, 0x40, 0x1a,
    0xfd, 0x60,

    /* U+0034 "4" */
    0x0, 0x0, 0xcf, 0x20, 0x0, 0x1, 0xff, 0x20,
    0x0, 0x9, 0xef, 0x20, 0x0, 0x1f, 0x6f, 0x20,
    0x0, 0x9b, 0x3f, 0x20, 0x1, 0xf3, 0x3f, 0x20,
    0x9, 0xb0, 0x3f, 0x20, 0x2f, 0x40, 0x3f, 0x20,
    0x8f, 0xff, 0xff, 0xf6, 0x13, 0x33, 0x6f, 0x51,
    0x0, 0x0, 0x3f, 0x20, 0x0, 0x0, 0x3f, 0x20,

    /* U+0035 "5" */
    0x1f, 0xff, 0xfe, 0x2, 0xf7, 0x66, 0x50, 0x3f,
    0x0, 0x0, 0x5, 0xf0, 0x0, 0x0, 0x6f, 0xdf,
    0xc1, 0x6, 0xe6, 0x6f, 0xa0, 0x0, 0x0, 0x6f,
    0x0, 0x0, 0x3, 0xf2, 0x42, 0x0, 0x3f, 0x2a,
    0xa0, 0x6, 0xf0, 0x5f, 0x75, 0xe9, 0x0, 0x6e,
    0xfa, 0x0,

    /* U+0036 "6" */
    0x0, 0x8d, 0xb0, 0x0, 0xbf, 0x73, 0x0, 0x4f,
    0x30, 0x0, 0x9, 0xc0, 0x0, 0x0, 0xcb, 0xcf,
    0xb0, 0xe, 0xf7, 0x5f, 0x90, 0xff, 0x0, 0x7e,
    0xf, 0x90, 0x4, 0xf1, 0xd8, 0x0, 0x4f, 0xa,
    0xc0, 0x8, 0xe0, 0x3f, 0x85, 0xf7, 0x0, 0x6e,
    0xf9, 0x0,

    /* U+0037 "7" */
    0x5f, 0xff, 0xff, 0xf3, 0x13, 0x33, 0x38, 0xf0,
    0x0, 0x0, 0xb, 0x90, 0x0, 0x0, 0x1f, 0x40,
    0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0xc9, 0x0,
    0x0, 0x2, 0xf3, 0x0, 0x0, 0x8, 0xd0, 0x0,
    0x0, 0xe, 0x80, 0x0, 0x0, 0x4f, 0x20, 0x0,
    0x0, 0xac, 0x0, 0x0, 0x0, 0xf7, 0x0, 0x0,

    /* U+0038 "8" */
    0x0, 0x9f, 0xe8, 0x0, 0x8f, 0x67, 0xf6, 0xd,
    0x90, 0xb, 0xb0, 0xd9, 0x0, 0xbb, 0x8, 0xf5,
    0x6f, 0x60, 0xf, 0xff, 0xf0, 0x8, 0xd1, 0x2e,
    0x70, 0xe6, 0x0, 0x8d, 0xf, 0x50, 0x6, 0xf0,
    0xf7, 0x0, 0x9d, 0x9, 0xe5, 0x6f, 0x70, 0x9,
    0xfe, 0x80,

    /* U+0039 "9" */
    0x0, 0xaf, 0xe5, 0x0, 0x8e, 0x5a, 0xf2, 0xe,
    0x70, 0xe, 0x81, 0xf3, 0x0, 0xab, 0x2f, 0x30,
    0xb, 0xf0, 0xf5, 0x0, 0xff, 0xb, 0xd2, 0x5f,
    0xc0, 0x2e, 0xfe, 0xbb, 0x0, 0x2, 0xc, 0x80,
    0x0, 0x3, 0xf3, 0x0, 0x47, 0xea, 0x0, 0xc,
    0xd8, 0x0,

    /* U+003A ":" */
    0xba, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x88,
    0xba,

    /* U+003B ";" */
    0xe, 0x70, 0xb5, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x95, 0xe, 0x80, 0xf5, 0x6e,
    0x1, 0x20,

    /* U+003C "<" */
    0x0, 0x0, 0x2a, 0x0, 0x8, 0xfd, 0x6, 0xee,
    0x60, 0x9f, 0x80, 0x0, 0x2c, 0xe7, 0x0, 0x0,
    0x6e, 0xe7, 0x0, 0x0, 0x8f, 0x0, 0x0, 0x2,

    /* U+003D "=" */
    0x1, 0x11, 0x10, 0xdf, 0xff, 0xfa, 0x34, 0x44,
    0x42, 0x1, 0x11, 0x10, 0xdf, 0xff, 0xfa, 0x34,
    0x44, 0x42,

    /* U+003E ">" */
    0xa3, 0x0, 0x0, 0xcf, 0xa2, 0x0, 0x4, 0xcf,
    0x81, 0x0, 0x5, 0xff, 0x0, 0x6e, 0xe5, 0x6e,
    0xf8, 0x0, 0xe9, 0x10, 0x0, 0x20, 0x0, 0x0,

    /* U+003F "?" */
    0x4, 0xdf, 0xc2, 0x1, 0xfb, 0x6d, 0xc0, 0x4e,
    0x10, 0x6f, 0x0, 0x0, 0x5, 0xf0, 0x0, 0x0,
    0xbb, 0x0, 0x0, 0x6f, 0x30, 0x0, 0x1f, 0x70,
    0x0, 0x6, 0xf0, 0x0, 0x0, 0x58, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x49, 0x0, 0x0, 0x6,
    0xc0, 0x0,

    /* U+0040 "@" */
    0x0, 0x0, 0x8d, 0xfd, 0x80, 0x0, 0x0, 0x1d,
    0xa3, 0x13, 0xac, 0x0, 0x0, 0xb9, 0x0, 0x0,
    0x9, 0x80, 0x3, 0xe0, 0x6, 0xdc, 0x21, 0xd0,
    0x8, 0x80, 0x4d, 0x3f, 0xa0, 0xc3, 0xd, 0x30,
    0xb6, 0xa, 0x60, 0x86, 0xf, 0x10, 0xf2, 0xc,
    0x50, 0x77, 0x1f, 0x2, 0xf0, 0xd, 0x40, 0x77,
    0xf, 0x4, 0xe0, 0xf, 0x30, 0x86, 0xf, 0x3,
    0xe0, 0xf, 0x20, 0xb3, 0xd, 0x40, 0xf3, 0x7f,
    0x54, 0xd0, 0x8, 0x90, 0x7f, 0x74, 0xed, 0x20,
    0x2, 0xe2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6e,
    0x61, 0x14, 0x20, 0x0, 0x0, 0x4, 0xcf, 0xeb,
    0x20, 0x0,

    /* U+0041 "A" */
    0x0, 0x2, 0xf6, 0x0, 0x0, 0x0, 0x7f, 0xb0,
    0x0, 0x0, 0xc, 0xcf, 0x0, 0x0, 0x1, 0xf4,
    0xf4, 0x0, 0x0, 0x6f, 0xb, 0x90, 0x0, 0xa,
    0xa0, 0x6e, 0x0, 0x0, 0xf6, 0x2, 0xf3, 0x0,
    0x4f, 0x20, 0xe, 0x80, 0xa, 0xff, 0xff, 0xff,
    0x0, 0xec, 0x33, 0x38, 0xf2, 0x3f, 0x30, 0x0,
    0xf, 0x78, 0xf0, 0x0, 0x0, 0xbc,

    /* U+0042 "B" */
    0xcf, 0xff, 0xd6, 0xc, 0xc4, 0x5a, 0xf3, 0xca,
    0x0, 0xf, 0x7c, 0xa0, 0x0, 0xe8, 0xcb, 0x11,
    0x7f, 0x3c, 0xff, 0xff, 0x80, 0xcd, 0x76, 0x7f,
    0x3c, 0xa0, 0x0, 0xca, 0xca, 0x0, 0xa, 0xcc,
    0xa0, 0x0, 0xdb, 0xcc, 0x44, 0x9f, 0x5c, 0xff,
    0xfd, 0x60,

    /* U+0043 "C" */
    0x0, 0x3b, 0xfe, 0x90, 0x0, 0x1f, 0xc5, 0x6e,
    0xb0, 0x9, 0xe0, 0x0, 0x5f, 0x20, 0xd9, 0x0,
    0x1, 0xe4, 0xf, 0x70, 0x0, 0x0, 0x0, 0xf6,
    0x0, 0x0, 0x0, 0xf, 0x60, 0x0, 0x0, 0x0,
    0xf7, 0x0, 0x0, 0x0, 0xd, 0x90, 0x0, 0x1e,
    0x40, 0x9d, 0x0, 0x5, 0xf2, 0x1, 0xfb, 0x56,
    0xea, 0x0, 0x3, 0xcf, 0xe9, 0x0,

    /* U+0044 "D" */
    0xff, 0xff, 0xb3, 0x0, 0xdf, 0x46, 0xcf, 0x30,
    0xca, 0x0, 0xd, 0xb0, 0xca, 0x0, 0x7, 0xf0,
    0xca, 0x0, 0x4, 0xf1, 0xca, 0x0, 0x4, 0xf2,
    0xca, 0x0, 0x4, 0xf2, 0xca, 0x0, 0x5, 0xf1,
    0xca, 0x0, 0x7, 0xf0, 0xca, 0x0, 0xd, 0xb0,
    0xcf, 0x45, 0xcf, 0x30, 0xef, 0xff, 0xb3, 0x0,

    /* U+0045 "E" */
    0xcf, 0xff, 0xff, 0x4c, 0xd4, 0x44, 0x41, 0xca,
    0x0, 0x0, 0xc, 0xa0, 0x0, 0x0, 0xcb, 0x0,
    0x0, 0xc, 0xff, 0xff, 0xb0, 0xcc, 0x33, 0x32,
    0xc, 0xa0, 0x0, 0x0, 0xca, 0x0, 0x0, 0xc,
    0xa0, 0x0, 0x0, 0xcd, 0x44, 0x44, 0x1c, 0xff,
    0xff, 0xf5,

    /* U+0046 "F" */
    0xcf, 0xff, 0xff, 0x2c, 0xd4, 0x44, 0x40, 0xca,
    0x0, 0x0, 0xc, 0xa0, 0x0, 0x0, 0xca, 0x0,
    0x0, 0xc, 0xb0, 0x0, 0x0, 0xcf, 0xff, 0xf8,
    0xc, 0xd3, 0x33, 0x10, 0xca, 0x0, 0x0, 0xc,
    0xa0, 0x0, 0x0, 0xca, 0x0, 0x0, 0xc, 0xa0,
    0x0, 0x0,

    /* U+0047 "G" */
    0x0, 0x4c, 0xfe, 0x91, 0x0, 0x3f, 0xb5, 0x6f,
    0xb0, 0xb, 0xd0, 0x0, 0x6f, 0x20, 0xe8, 0x0,
    0x1, 0x92, 0xf, 0x70, 0x0, 0x0, 0x0, 0xf6,
    0x0, 0x0, 0x0, 0xf, 0x60, 0x2f, 0xff, 0x50,
    0xf7, 0x0, 0x34, 0xf5, 0xe, 0x90, 0x0, 0x1f,
    0x50, 0xae, 0x0, 0x1, 0xf5, 0x2, 0xfc, 0x55,
    0xbf, 0x30, 0x3, 0xbf, 0xfc, 0x30,

    /* U+0048 "H" */
    0xca, 0x0, 0x0, 0xca, 0xca, 0x0, 0x0, 0xca,
    0xca, 0x0, 0x0, 0xca, 0xca, 0x0, 0x0, 0xca,
    0xcb, 0x0, 0x0, 0xca, 0xcf, 0xff, 0xff, 0xfa,
    0xcc, 0x33, 0x33, 0xda, 0xca, 0x0, 0x0, 0xca,
    0xca, 0x0, 0x0, 0xca, 0xca, 0x0, 0x0, 0xca,
    0xca, 0x0, 0x0, 0xca, 0xca, 0x0, 0x0, 0xca,

    /* U+0049 "I" */
    0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,
    0xbb, 0xbb, 0xbb, 0xbb,

    /* U+004A "J" */
    0x0, 0x0, 0xd, 0x90, 0x0, 0x0, 0xd9, 0x0,
    0x0, 0xd, 0x90, 0x0, 0x0, 0xd9, 0x0, 0x0,
    0xd, 0x90, 0x0, 0x0, 0xd9, 0x0, 0x0, 0xd,
    0x90, 0x0, 0x0, 0xd9, 0x36, 0x0, 0xe, 0x96,
    0xf0, 0x1, 0xf7, 0x2f, 0xb5, 0xbf, 0x20, 0x4d,
    0xfd, 0x40,

    /* U+004B "K" */
    0xca, 0x0, 0xa, 0xe1, 0xca, 0x0, 0x5f, 0x50,
    0xca, 0x1, 0xea, 0x0, 0xca, 0xb, 0xe0, 0x0,
    0xca, 0x6f, 0x30, 0x0, 0xcd, 0xff, 0x0, 0x0,
    0xcf, 0xef, 0x60, 0x0, 0xcf, 0x19, 0xe1, 0x0,
    0xcc, 0x1, 0xf9, 0x0, 0xca, 0x0, 0x7f, 0x30,
    0xca, 0x0, 0xd, 0xc0, 0xca, 0x0, 0x5, 0xf6,

    /* U+004C "L" */
    0xca, 0x0, 0x0, 0xc, 0xa0, 0x0, 0x0, 0xca,
    0x0, 0x0, 0xc, 0xa0, 0x0, 0x0, 0xca, 0x0,
    0x0, 0xc, 0xa0, 0x0, 0x0, 0xca, 0x0, 0x0,
    0xc, 0xa0, 0x0, 0x0, 0xca, 0x0, 0x0, 0xc,
    0xa0, 0x0, 0x0, 0xcd, 0x44, 0x44, 0xc, 0xff,
    0xff, 0xf2,

    /* U+004D "M" */
    0xef, 0x30, 0x0, 0x2, 0xff, 0xcf, 0x80, 0x0,
    0x7, 0xfd, 0xcf, 0xd0, 0x0, 0xb, 0xfd, 0xcc,
    0xf2, 0x0, 0x1f, 0xcd, 0xc9, 0xe7, 0x0, 0x5f,
    0x8d, 0xc9, 0x9b, 0x0, 0xaa, 0x8d, 0xca, 0x4f,
    0x10, 0xf5, 0x8d, 0xca, 0xe, 0x54, 0xf0, 0x9d,
    0xca, 0x9, 0xa9, 0xb0, 0x9d, 0xca, 0x4, 0xfe,
    0x60, 0x9d, 0xca, 0x0, 0xff, 0x10, 0x9d, 0xca,
    0x0, 0xac, 0x0, 0x9d,

    /* U+004E "N" */
    0xce, 0x0, 0x0, 0xca, 0xcf, 0x60, 0x0, 0xca,
    0xcf, 0xe0, 0x0, 0xca, 0xcb, 0xe6, 0x0, 0xca,
    0xca, 0x7d, 0x0, 0xca, 0xca, 0xe, 0x60, 0xca,
    0xca, 0x7, 0xd0, 0xca, 0xca, 0x0, 0xe5, 0xca,
    0xca, 0x0, 0x8d, 0xca, 0xca, 0x0, 0x1f, 0xfa,
    0xca, 0x0, 0x8, 0xfa, 0xca, 0x0, 0x1, 0xfa,

    /* U+004F "O" */
    0x0, 0x3c, 0xfe, 0x90, 0x0, 0x2f, 0xc6, 0x7f,
    0xb0, 0xa, 0xe0, 0x0, 0x4f, 0x30, 0xe8, 0x0,
    0x0, 0xe7, 0xf, 0x60, 0x0, 0xd, 0x90, 0xf6,
    0x0, 0x0, 0xca, 0xf, 0x60, 0x0, 0xc, 0xa0,
    0xf6, 0x0, 0x0, 0xd9, 0xe, 0x80, 0x0, 0xe,
    0x70, 0x9e, 0x0, 0x4, 0xf3, 0x2, 0xfc, 0x67,
    0xec, 0x0, 0x3, 0xcf, 0xe9, 0x10,

    /* U+0050 "P" */
    0xcf, 0xff, 0xe9, 0x0, 0xcc, 0x44, 0x6f, 0xa0,
    0xca, 0x0, 0x7, 0xf1, 0xca, 0x0, 0x3, 0xf3,
    0xca, 0x0, 0x5, 0xf2, 0xcb, 0x0, 0x2d, 0xd0,
    0xcf, 0xff, 0xfd, 0x30, 0xcd, 0x33, 0x20, 0x0,
    0xca, 0x0, 0x0, 0x0, 0xca, 0x0, 0x0, 0x0,
    0xca, 0x0, 0x0, 0x0, 0xca, 0x0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x0, 0x4c, 0xfe, 0x90, 0x0, 0x3f, 0xc6, 0x8f,
    0xa0, 0xb, 0xd0, 0x0, 0x5f, 0x20, 0xf7, 0x0,
    0x0, 0xf6, 0xf, 0x50, 0x0, 0xe, 0x81, 0xf5,
    0x0, 0x0, 0xd9, 0x1f, 0x50, 0x0, 0xd, 0x90,
    0xf5, 0x0, 0x0, 0xe8, 0xf, 0x70, 0x0, 0xf,
    0x60, 0xbd, 0x0, 0x5, 0xf2, 0x3, 0xfb, 0x68,
    0xfb, 0x0, 0x4, 0xcf, 0xff, 0x50, 0x0, 0x0,
    0x0, 0xaf, 0x50, 0x0, 0x0, 0x0, 0x82,

    /* U+0052 "R" */
    0xcf, 0xff, 0xd6, 0x0, 0xcc, 0x45, 0xaf, 0x40,
    0xca, 0x0, 0xd, 0xa0, 0xca, 0x0, 0xa, 0xc0,
    0xca, 0x0, 0xc, 0xb0, 0xcb, 0x1, 0x7f, 0x50,
    0xcf, 0xff, 0xf8, 0x0, 0xcd, 0x37, 0xf4, 0x0,
    0xca, 0x0, 0xcb, 0x0, 0xca, 0x0, 0x5f, 0x20,
    0xca, 0x0, 0xe, 0x90, 0xca, 0x0, 0x8, 0xf1,

    /* U+0053 "S" */
    0x0, 0x8d, 0xfc, 0x30, 0x8, 0xf7, 0x5b, 0xe1,
    0xe, 0x90, 0x0, 0xf7, 0xf, 0x70, 0x0, 0x75,
    0xb, 0xe3, 0x0, 0x0, 0x1, 0xcf, 0xb4, 0x0,
    0x0, 0x5, 0xcf, 0xa0, 0x0, 0x0, 0x6, 0xf5,
    0x29, 0x10, 0x0, 0xd9, 0x2f, 0x50, 0x0, 0xe8,
    0xa, 0xe7, 0x5a, 0xf3, 0x0, 0x8d, 0xfc, 0x40,

    /* U+0054 "T" */
    0x8f, 0xff, 0xff, 0xfe, 0x24, 0x4d, 0xf4, 0x44,
    0x0, 0x8, 0xe0, 0x0, 0x0, 0x8, 0xe0, 0x0,
    0x0, 0x8, 0xe0, 0x0, 0x0, 0x8, 0xe0, 0x0,
    0x0, 0x8, 0xe0, 0x0, 0x0, 0x8, 0xe0, 0x0,
    0x0, 0x8, 0xe0, 0x0, 0x0, 0x8, 0xe0, 0x0,
    0x0, 0x8, 0xe0, 0x0, 0x0, 0x8, 0xe0, 0x0,

    /* U+0055 "U" */
    0xf7, 0x0, 0x6, 0xf0, 0xf7, 0x0, 0x6, 0xf0,
    0xf7, 0x0, 0x6, 0xf0, 0xf7, 0x0, 0x6, 0xf0,
    0xf7, 0x0, 0x6, 0xf0, 0xf7, 0x0, 0x6, 0xf0,
    0xf7, 0x0, 0x6, 0xf0, 0xf7, 0x0, 0x6, 0xf0,
    0xf7, 0x0, 0x7, 0xf0, 0xda, 0x0, 0x9, 0xd0,
    0x7f, 0x85, 0x8f, 0x70, 0x7, 0xdf, 0xd7, 0x0,

    /* U+0056 "V" */
    0x8f, 0x0, 0x0, 0xf, 0x83, 0xf4, 0x0, 0x4,
    0xf3, 0xe, 0x90, 0x0, 0x9e, 0x0, 0xad, 0x0,
    0xd, 0x90, 0x5, 0xf1, 0x1, 0xf5, 0x0, 0xf,
    0x50, 0x6f, 0x0, 0x0, 0xba, 0xa, 0xb0, 0x0,
    0x7, 0xe0, 0xe7, 0x0, 0x0, 0x2f, 0x5f, 0x20,
    0x0, 0x0, 0xde, 0xd0, 0x0, 0x0, 0x9, 0xf9,
    0x0, 0x0, 0x0, 0x4f, 0x40, 0x0,

    /* U+0057 "W" */
    0x5f, 0x10, 0xa, 0xf0, 0x0, 0xba, 0x2f, 0x30,
    0xb, 0xf1, 0x0, 0xe7, 0xf, 0x60, 0xe, 0xf5,
    0x1, 0xf4, 0xc, 0x90, 0x2f, 0xa8, 0x4, 0xf1,
    0x9, 0xc0, 0x6c, 0x6b, 0x6, 0xe0, 0x6, 0xe0,
    0x99, 0x3f, 0x9, 0xb0, 0x3, 0xf1, 0xd5, 0xf,
    0x2c, 0x80, 0x0, 0xf5, 0xf2, 0xc, 0x6e, 0x50,
    0x0, 0xda, 0xe0, 0x8, 0xaf, 0x20, 0x0, 0xaf,
    0xa0, 0x5, 0xff, 0x0, 0x0, 0x7f, 0x70, 0x1,
    0xfc, 0x0, 0x0, 0x4f, 0x30, 0x0, 0xfb, 0x0,

    /* U+0058 "X" */
    0x2f, 0x80, 0x0, 0xae, 0x0, 0xae, 0x0, 0x2f,
    0x70, 0x2, 0xf7, 0x9, 0xe0, 0x0, 0xa, 0xe1,
    0xf7, 0x0, 0x0, 0x2f, 0xde, 0x0, 0x0, 0x0,
    0xaf, 0x80, 0x0, 0x0, 0xb, 0xf8, 0x0, 0x0,
    0x3, 0xfc, 0xf1, 0x0, 0x0, 0xbd, 0x1f, 0x80,
    0x0, 0x3f, 0x60, 0x8f, 0x10, 0xb, 0xe0, 0x1,
    0xf8, 0x3, 0xf7, 0x0, 0x9, 0xf1,

    /* U+0059 "Y" */
    0x8f, 0x10, 0x0, 0xae, 0x2, 0xf7, 0x0, 0x1f,
    0x70, 0xb, 0xd0, 0x7, 0xf1, 0x0, 0x4f, 0x30,
    0xda, 0x0, 0x0, 0xd9, 0x3f, 0x30, 0x0, 0x6,
    0xfa, 0xc0, 0x0, 0x0, 0xe, 0xf5, 0x0, 0x0,
    0x0, 0x9f, 0x0, 0x0, 0x0, 0x8, 0xe0, 0x0,
    0x0, 0x0, 0x8e, 0x0, 0x0, 0x0, 0x8, 0xe0,
    0x0, 0x0, 0x0, 0x8e, 0x0, 0x0,

    /* U+005A "Z" */
    0x3f, 0xff, 0xff, 0xf8, 0x14, 0x44, 0x48, 0xf4,
    0x0, 0x0, 0xc, 0xc0, 0x0, 0x0, 0x4f, 0x30,
    0x0, 0x0, 0xda, 0x0, 0x0, 0x6, 0xf2, 0x0,
    0x0, 0xe, 0x90, 0x0, 0x0, 0x7f, 0x10, 0x0,
    0x1, 0xf8, 0x0, 0x0, 0x8, 0xe0, 0x0, 0x0,
    0x1f, 0xb4, 0x44, 0x43, 0x4f, 0xff, 0xff, 0xfb,

    /* U+005B "[" */
    0x0, 0xe, 0xfa, 0xe9, 0x2e, 0x70, 0xe7, 0xe,
    0x70, 0xe7, 0xe, 0x70, 0xe7, 0xe, 0x70, 0xe7,
    0xe, 0x70, 0xe7, 0xe, 0x70, 0xe7, 0xe, 0x70,
    0xef, 0xa2, 0x32,

    /* U+005C "\\" */
    0x7d, 0x0, 0x0, 0x2f, 0x20, 0x0, 0xd, 0x70,
    0x0, 0x8, 0xc0, 0x0, 0x3, 0xf1, 0x0, 0x0,
    0xe6, 0x0, 0x0, 0x9b, 0x0, 0x0, 0x4f, 0x0,
    0x0, 0xf, 0x50, 0x0, 0xa, 0x90, 0x0, 0x6,
    0xe0, 0x0, 0x1, 0xf3, 0x0, 0x0, 0xc8,

    /* U+005D "]" */
    0x0, 0xc, 0xfd, 0x2a, 0xd0, 0x8d, 0x8, 0xd0,
    0x8d, 0x8, 0xd0, 0x8d, 0x8, 0xd0, 0x8d, 0x8,
    0xd0, 0x8d, 0x8, 0xd0, 0x8d, 0x8, 0xd0, 0x8d,
    0xcf, 0xd2, 0x32,

    /* U+005E "^" */
    0x0, 0xfd, 0x0, 0x0, 0xff, 0x0, 0x4, 0xde,
    0x30, 0xa, 0x89, 0x90, 0xf, 0x35, 0xe0, 0x4f,
    0x0, 0xf3,

    /* U+005F "_" */
    0x0, 0x0, 0x0, 0xc, 0xff, 0xff, 0xf4, 0x23,
    0x33, 0x33, 0x0,

    /* U+0060 "`" */
    0x28, 0x20, 0xb, 0xc0, 0x1, 0xd6,

    /* U+0061 "a" */
    0x1, 0xae, 0xe9, 0x0, 0xbd, 0x47, 0xf5, 0x4,
    0x20, 0xd, 0x80, 0x8, 0xde, 0xf9, 0x9, 0xe5,
    0x2d, 0x90, 0xf6, 0x0, 0xd9, 0x1f, 0x50, 0xf,
    0x90, 0xec, 0x5a, 0xf9, 0x3, 0xdf, 0x89, 0xa0,

    /* U+0062 "b" */
    0xf6, 0x0, 0x0, 0xf, 0x60, 0x0, 0x0, 0xf6,
    0x0, 0x0, 0xf, 0x8c, 0xfb, 0x10, 0xff, 0x76,
    0xeb, 0xf, 0xd0, 0x7, 0xf0, 0xf9, 0x0, 0x4f,
    0x2f, 0x90, 0x3, 0xf2, 0xf9, 0x0, 0x4f, 0x1f,
    0xc0, 0x6, 0xf0, 0xff, 0x33, 0xda, 0xf, 0x7c,
    0xfb, 0x10,

    /* U+0063 "c" */
    0x0, 0xaf, 0xe8, 0x0, 0xae, 0x56, 0xf6, 0xf,
    0x50, 0x9, 0xb2, 0xf2, 0x0, 0x12, 0x3f, 0x20,
    0x0, 0x2, 0xf2, 0x0, 0x0, 0xf, 0x50, 0x8,
    0xb0, 0xad, 0x55, 0xf6, 0x0, 0xaf, 0xe8, 0x0,

    /* U+0064 "d" */
    0x0, 0x0, 0x8, 0xd0, 0x0, 0x0, 0x8d, 0x0,
    0x0, 0x8, 0xd0, 0x2b, 0xfc, 0x9d, 0xb, 0xe6,
    0x7f, 0xd1, 0xf5, 0x0, 0xfd, 0x3f, 0x20, 0xb,
    0xf3, 0xf2, 0x0, 0xbf, 0x2f, 0x20, 0xb, 0xf1,
    0xf4, 0x0, 0xfe, 0xb, 0xd3, 0x4f, 0xd0, 0x1b,
    0xfc, 0x8d,

    /* U+0065 "e" */
    0x0, 0x9e, 0xe8, 0x0, 0xae, 0x56, 0xf5, 0xf,
    0x60, 0xb, 0xa2, 0xf3, 0x0, 0x8c, 0x3f, 0xff,
    0xff, 0xd3, 0xf6, 0x33, 0x32, 0x1f, 0x60, 0x0,
    0x0, 0xae, 0x54, 0xa8, 0x1, 0x9e, 0xeb, 0x20,

    /* U+0066 "f" */
    0x0, 0x0, 0x0, 0x6, 0xfd, 0x1, 0xf9, 0x30,
    0x4f, 0x10, 0x5, 0xf0, 0x7, 0xff, 0xf7, 0x18,
    0xf3, 0x10, 0x5f, 0x0, 0x5, 0xf0, 0x0, 0x5f,
    0x0, 0x5, 0xf0, 0x0, 0x5f, 0x0, 0x5, 0xf0,
    0x0, 0x5f, 0x0,

    /* U+0067 "g" */
    0x2, 0xbf, 0xc8, 0xd0, 0xcd, 0x34, 0xfd, 0x1f,
    0x50, 0xe, 0xe3, 0xf2, 0x0, 0xbf, 0x3f, 0x20,
    0xb, 0xf2, 0xf2, 0x0, 0xbf, 0x1f, 0x50, 0xf,
    0xe0, 0xbe, 0x66, 0xfd, 0x1, 0xbf, 0xc9, 0xd0,
    0x0, 0x0, 0x9c, 0x7, 0x94, 0x7f, 0x70, 0x2b,
    0xfe, 0x80,

    /* U+0068 "h" */
    0xf6, 0x0, 0x0, 0xf6, 0x0, 0x0, 0xf6, 0x0,
    0x0, 0xf8, 0xbf, 0xa0, 0xff, 0x77, 0xf6, 0xff,
    0x0, 0xba, 0xfa, 0x0, 0xab, 0xf8, 0x0, 0xab,
    0xf6, 0x0, 0xab, 0xf6, 0x0, 0xab, 0xf6, 0x0,
    0xab, 0xf6, 0x0, 0xab,

    /* U+0069 "i" */
    0xb7, 0x74, 0x0, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8,
    0xd8, 0xd8, 0xd8, 0xd8,

    /* U+006A "j" */
    0x0, 0xd5, 0x0, 0x83, 0x0, 0x0, 0x0, 0xe7,
    0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7,
    0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7, 0x0, 0xe7,
    0x0, 0xe7, 0x16, 0xf4, 0x2f, 0xb0,

    /* U+006B "k" */
    0xf7, 0x0, 0x0, 0xf, 0x70, 0x0, 0x0, 0xf7,
    0x0, 0x0, 0xf, 0x70, 0x4f, 0x50, 0xf7, 0x1e,
    0xa0, 0xf, 0x7a, 0xd0, 0x0, 0xfc, 0xf4, 0x0,
    0xf, 0xff, 0x70, 0x0, 0xff, 0x7f, 0x10, 0xf,
    0x70, 0xe9, 0x0, 0xf7, 0x6, 0xf3, 0xf, 0x70,
    0xd, 0xc0,

    /* U+006C "l" */
    0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8,
    0xd8, 0xd8, 0xd8, 0xd8,

    /* U+006D "m" */
    0xf8, 0xdf, 0xa1, 0xbf, 0xc2, 0xff, 0x35, 0xff,
    0x63, 0xcb, 0xfc, 0x0, 0xdf, 0x0, 0x6e, 0xf9,
    0x0, 0xcf, 0x0, 0x6f, 0xf6, 0x0, 0xab, 0x0,
    0x6f, 0xf6, 0x0, 0xab, 0x0, 0x6f, 0xf6, 0x0,
    0xab, 0x0, 0x6f, 0xf6, 0x0, 0xab, 0x0, 0x6f,
    0xf6, 0x0, 0xab, 0x0, 0x6f,

    /* U+006E "n" */
    0xf7, 0xcf, 0xa0, 0xff, 0x44, 0xf6, 0xfd, 0x0,
    0xba, 0xf9, 0x0, 0xab, 0xf6, 0x0, 0xab, 0xf6,
    0x0, 0xab, 0xf6, 0x0, 0xab, 0xf6, 0x0, 0xab,
    0xf6, 0x0, 0xab,

    /* U+006F "o" */
    0x0, 0x9e, 0xf9, 0x0, 0x9, 0xf6, 0x5e, 0xa0,
    0xf, 0x70, 0x6, 0xf1, 0x2f, 0x30, 0x2, 0xf3,
    0x3f, 0x20, 0x1, 0xf4, 0x2f, 0x30, 0x2, 0xf3,
    0xf, 0x60, 0x5, 0xf1, 0x9, 0xe5, 0x5e, 0x90,
    0x0, 0x9e, 0xe9, 0x0,

    /* U+0070 "p" */
    0xf7, 0xcf, 0xb1, 0xf, 0xf4, 0x4e, 0xb0, 0xfb,
    0x0, 0x7f, 0xf, 0x70, 0x4, 0xf2, 0xf7, 0x0,
    0x3f, 0x2f, 0x70, 0x4, 0xf1, 0xfc, 0x0, 0x7f,
    0xf, 0xf4, 0x5e, 0xa0, 0xf9, 0xdf, 0xb1, 0xf,
    0x60, 0x0, 0x0, 0xf6, 0x0, 0x0, 0xf, 0x60,
    0x0, 0x0,

    /* U+0071 "q" */
    0x2, 0xbf, 0xc9, 0xd0, 0xcd, 0x33, 0xfd, 0x1f,
    0x50, 0xe, 0xf3, 0xf2, 0x0, 0xaf, 0x3f, 0x20,
    0xa, 0xf3, 0xf2, 0x0, 0xaf, 0x1f, 0x50, 0xf,
    0xe0, 0xbe, 0x55, 0xfd, 0x2, 0xbf, 0xca, 0xd0,
    0x0, 0x0, 0x8d, 0x0, 0x0, 0x8, 0xd0, 0x0,
    0x0, 0x8d,

    /* U+0072 "r" */
    0xf9, 0xe8, 0xff, 0x62, 0xfe, 0x0, 0xf9, 0x0,
    0xf6, 0x0, 0xf6, 0x0, 0xf6, 0x0, 0xf6, 0x0,
    0xf6, 0x0,

    /* U+0073 "s" */
    0x1, 0xbf, 0xe6, 0x0, 0xbc, 0x49, 0xf2, 0xe,
    0x70, 0xa, 0x40, 0xae, 0x50, 0x0, 0x0, 0x8f,
    0xe5, 0x0, 0x0, 0x19, 0xf4, 0x2c, 0x30, 0xe,
    0x70, 0xdc, 0x47, 0xf4, 0x2, 0xcf, 0xe7, 0x0,

    /* U+0074 "t" */
    0x8, 0xd0, 0x0, 0x8d, 0x0, 0xdf, 0xff, 0x22,
    0xbf, 0x20, 0x8, 0xd0, 0x0, 0x8d, 0x0, 0x8,
    0xd0, 0x0, 0x8d, 0x0, 0x8, 0xd0, 0x0, 0x7f,
    0x50, 0x1, 0xcf, 0x10,

    /* U+0075 "u" */
    0xf6, 0x0, 0xbb, 0xf6, 0x0, 0xbb, 0xf6, 0x0,
    0xbb, 0xf6, 0x0, 0xbb, 0xf6, 0x0, 0xbb, 0xf6,
    0x0, 0xfc, 0xe7, 0x0, 0xfb, 0xad, 0x26, 0xfb,
    0x2c, 0xfb, 0xbb,

    /* U+0076 "v" */
    0x8e, 0x0, 0x1f, 0x43, 0xf2, 0x4, 0xf0, 0xe,
    0x60, 0x8c, 0x0, 0xaa, 0xc, 0x70, 0x5, 0xe0,
    0xf3, 0x0, 0x1f, 0x6e, 0x0, 0x0, 0xce, 0xa0,
    0x0, 0x8, 0xf5, 0x0, 0x0, 0x3f, 0x10, 0x0,

    /* U+0077 "w" */
    0x7d, 0x0, 0xaf, 0x0, 0x7d, 0x4f, 0x10, 0xdf,
    0x10, 0xaa, 0xf, 0x40, 0xff, 0x50, 0xe6, 0xc,
    0x73, 0xe9, 0x91, 0xf2, 0x9, 0xb7, 0xa5, 0xd4,
    0xf0, 0x5, 0xeb, 0x61, 0xf9, 0xb0, 0x1, 0xff,
    0x20, 0xdf, 0x70, 0x0, 0xff, 0x0, 0x8f, 0x40,
    0x0, 0xef, 0x0, 0x4f, 0x0,

    /* U+0078 "x" */
    0x4f, 0x40, 0x4f, 0x40, 0xbb, 0xb, 0xc0, 0x3,
    0xf5, 0xf3, 0x0, 0xb, 0xfb, 0x0, 0x0, 0x5f,
    0x50, 0x0, 0xc, 0xfc, 0x0, 0x4, 0xf4, 0xf4,
    0x0, 0xca, 0xa, 0xc0, 0x5f, 0x30, 0x3f, 0x50,

    /* U+0079 "y" */
    0x9e, 0x0, 0x3f, 0x34, 0xf2, 0x7, 0xe0, 0xf,
    0x60, 0xba, 0x0, 0xba, 0xf, 0x50, 0x6, 0xe3,
    0xf1, 0x0, 0x1f, 0xac, 0x0, 0x0, 0xcf, 0x80,
    0x0, 0x8, 0xf3, 0x0, 0x0, 0x6f, 0x0, 0x0,
    0x8, 0xa0, 0x0, 0x16, 0xf4, 0x0, 0x4, 0xf8,
    0x0, 0x0,

    /* U+007A "z" */
    0x3f, 0xff, 0xff, 0x30, 0x44, 0x4c, 0xf0, 0x0,
    0x2, 0xf6, 0x0, 0x0, 0xbc, 0x0, 0x0, 0x4f,
    0x30, 0x0, 0xd, 0xa0, 0x0, 0x7, 0xf1, 0x0,
    0x1, 0xfb, 0x33, 0x31, 0x4f, 0xff, 0xff, 0x60,

    /* U+007B "{" */
    0x0, 0x1, 0x20, 0x2, 0xe5, 0x0, 0xca, 0x0,
    0xf, 0x50, 0x1, 0xf4, 0x0, 0x1f, 0x40, 0x2,
    0xf4, 0x0, 0x8f, 0x0, 0xdf, 0x80, 0x0, 0x8e,
    0x0, 0x2, 0xf3, 0x0, 0x1f, 0x40, 0x1, 0xf4,
    0x0, 0xf, 0x50, 0x0, 0xc9, 0x0, 0x4, 0xf5,
    0x0, 0x3, 0x30,

    /* U+007C "|" */
    0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8,
    0xa8, 0xa8, 0xa8, 0xa8, 0xa8, 0xa8,

    /* U+007D "}" */
    0x31, 0x0, 0x7, 0xe2, 0x0, 0xb, 0xa0, 0x0,
    0x7d, 0x0, 0x6, 0xf0, 0x0, 0x6f, 0x0, 0x5,
    0xf0, 0x0, 0x1f, 0x80, 0x0, 0x7f, 0x80, 0x1f,
    0x70, 0x5, 0xf0, 0x0, 0x6f, 0x0, 0x6, 0xf0,
    0x0, 0x7d, 0x0, 0xb, 0xa0, 0x7, 0xe2, 0x0,
    0x31, 0x0, 0x0,

    /* U+007E "~" */
    0x1, 0xce, 0x60, 0xb, 0x60, 0xba, 0x5f, 0x73,
    0xf3, 0xe, 0x30, 0x4f, 0xfa, 0x0, 0x0, 0x0,
    0x12, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 59, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 63, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 22, .adv_w = 140, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 126, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 134, .adv_w = 162, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 139, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 45, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 252, .adv_w = 80, .box_w = 4, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 288, .adv_w = 82, .box_w = 5, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 333, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 358, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 50, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 406, .adv_w = 64, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 412, .adv_w = 68, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 95, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 453, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 126, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 126, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 126, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 747, .adv_w = 126, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 879, .adv_w = 60, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 52, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 906, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 930, .adv_w = 123, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 948, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 972, .adv_w = 108, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1014, .adv_w = 197, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1104, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1158, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1200, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1254, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1302, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1344, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1386, .adv_w = 151, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1440, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1488, .adv_w = 64, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1500, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1542, .adv_w = 140, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1590, .adv_w = 122, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1632, .adv_w = 193, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1692, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1740, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1794, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1842, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1905, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1953, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2001, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2049, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2097, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2151, .adv_w = 195, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2223, .adv_w = 141, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2277, .adv_w = 134, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2331, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2379, .adv_w = 64, .box_w = 3, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2406, .adv_w = 95, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2445, .adv_w = 64, .box_w = 3, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2472, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2490, .adv_w = 104, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2501, .adv_w = 79, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 2507, .adv_w = 123, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2539, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2581, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2613, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2655, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2687, .adv_w = 81, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2722, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2764, .adv_w = 124, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2800, .adv_w = 59, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2812, .adv_w = 57, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 2842, .adv_w = 115, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2884, .adv_w = 59, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2896, .adv_w = 193, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2941, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2968, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3004, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3046, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3088, .adv_w = 78, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3106, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3138, .adv_w = 76, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3166, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3193, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3225, .adv_w = 166, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3270, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3302, .adv_w = 107, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3344, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3376, .adv_w = 79, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3419, .adv_w = 63, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3433, .adv_w = 79, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3476, .adv_w = 151, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 3,
    3, 8,
    8, 3,
    8, 8,
    13, 3,
    13, 8,
    15, 3,
    15, 8,
    16, 16
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -13, -13, -13, -13, -21, -21, -21, -21,
    -28
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 9,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t RobotoCondensedVariableFont_wght16 = {
#else
lv_font_t RobotoCondensedVariableFont_wght16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if ROBOTOCONDENSEDVARIABLEFONT_WGHT16*/

