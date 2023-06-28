#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_

#include "common.h"

//const uint8_t oled_font_6x8[] = {
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 00 space
//    0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, // 01 !
//    0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // 02 "
//    0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, // 03 #
//    0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12, // 04 $
//    0x00, 0x23, 0x13, 0x08, 0x64, 0x62, // 05 %
//    0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // 06 &
//    0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // 07 '
//    0x00, 0x00, 0x1C, 0x22, 0x41, 0x00, // 08 (
//    0x00, 0x00, 0x41, 0x22, 0x1C, 0x00, // 09 )
//    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // 0a *
//    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // 0b +
//    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // 0c ,
//    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 0d -
//    0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // 0e .
//    0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // 0f /
//
//    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 10 0
//    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 11 1
//    0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 12 2
//    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 13 3
//    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 14 4
//    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 15 5
//    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 16 6
//    0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 17 7
//    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 18 8
//    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 19 9
//    0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // 1a :
//    0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // 1b ;
//    0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // 1c <
//    0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // 1d =
//    0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // 1e >
//    0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // 1f ?
//
//    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // 20 @
//    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // 21 A
//    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // 22 B
//    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // 23 C
//    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // 24 D
//    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // 25 E
//    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // 26 F
//    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // 27 G
//    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // 28 H
//    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // 29 I
//    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // 2a J
//    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // 2b K
//    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // 2c L
//    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // 2d M
//    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // 2e N
//    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // 2f O
//
//    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // 30 P
//    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // 31 Q
//    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // 32 R
//    0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // 33 S
//    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // 34 T
//    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // 35 U
//    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // 36 V
//    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // 37 W
//    0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // 38 X
//    0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // 39 Y
//    0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // 3a Z
//    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // 3b [
//    0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, // 3c backslash
//    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // 3d ]
//    0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // 3e ^
//    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // 3f _
//
//    0x00, 0x00, 0x03, 0x05, 0x00, 0x00, // 40 `
//    0x00, 0x20, 0x54, 0x54, 0x78, 0x40, // 41 a
//    0x00, 0x7F, 0x28, 0x44, 0x44, 0x38, // 42 b
//    0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // 43 c
//    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // 44 d
//    0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // 45 e
//    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // 46 f
//    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // 47 g
//    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // 48 h
//    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // 49 i
//    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // 4a j
//    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // 4b k
//    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // 4c l
//    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // 4d m
//    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // 4e n
//    0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // 4f o
//
//    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // 50 p
//    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // 51 q
//    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // 52 r
//    0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // 53 s
//    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // 54 t
//    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // 55 u
//    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // 56 v
//    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // 57 w
//    0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // 58 x
//    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // 59 y
//    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // 5a z
//    0x00, 0x00, 0x10, 0x7C, 0x82, 0x00, // 5b {
//    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, // 5c |
//    0x00, 0x00, 0x82, 0x7C, 0x10, 0x00, // 5d }
//    0x00, 0x10, 0x08, 0x10, 0x20, 0x10, // 5e ~
//	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 5f unknown character
//};

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_ */
