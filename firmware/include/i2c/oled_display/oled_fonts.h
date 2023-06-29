#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_

#include "common.h"

#define FONT_DIFF		32


#define FONT_6x8_COL	6
#define FONT_6x8_STR	8

#define FONT_12x16_COL	12
#define FONT_12x16_STR	16

uint8_t font6x8GetElement(char symb, uint8_t colom);

uint8_t font12x16GetElement(char symb, uint8_t colom);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_ */
