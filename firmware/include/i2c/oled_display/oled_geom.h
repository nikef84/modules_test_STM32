#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_GEOM_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_GEOM_H_

#include "oled_basic.h"


void oledDrawLineCoord(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void oledDrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);
void oledDrawCircle(uint8_t X1, uint8_t Y1, uint8_t R);
void oledFillSpace(uint8_t x, uint8_t y);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_GEOM_H_ */
