#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_

#include "oled_basic.h"
#include "oled_fonts.h"
#include "string.h"
#include "math.h"


void oledPrintText6x8(char *text, uint8_t x, uint8_t y);

void oledPrintText12x16(char *text, uint8_t x, uint8_t y);

uint8_t oledPrintInteger6x8(int32_t integer, uint8_t x, uint8_t y);

void oledPrintFloat6x8(float num, uint8_t num_after_point, uint8_t x, uint8_t y);

uint8_t oledPrintText(char *text, uint8_t x, uint8_t y);

void oledSetFont(uint8_t new_font);
uint8_t oledGetFont(void);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_ */
