#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_

#include "oled_basic.h"
#include "oled_fonts.h"
#include "string.h"


void oledPrintText6x8(char *text, uint8_t x, uint8_t y);

void oledPrintText12x16(char *text, uint8_t x, uint8_t y);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_ */
