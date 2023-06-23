#ifndef INCLUDE_I2C_OLED_DISPLAY_H_
#define INCLUDE_I2C_OLED_DISPLAY_H_

#include "common.h"
#include "i2c_lld.h"
#include "stdlib.h"

#define OLED_ADDR		0x3C

void oledInit(void);
void oledUpdatePic(void);
void oledClear(void);
void oledRegisterWriteFour(uint8_t reg_address, uint8_t data);
void oledRegisterWriteSix(uint8_t reg_address, uint8_t data, uint8_t data1);
void oledRegisterWriteTwo(uint8_t reg_address);
void oledDrawPixel(uint8_t x, uint8_t y);
void oledDrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void oledDrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);
void oledDrawCircle(uint8_t X1, uint8_t Y1, uint8_t R);

#endif /* INCLUDE_I2C_OLED_DISPLAY_H_ */
