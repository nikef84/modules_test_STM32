#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_BASIC_IMG_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_BASIC_IMG_H_

#include "oled_basic.h"

#define IMG_ALARM					0
#define IMG_ANTENNA					1
#define IMG_ARROW_DOWN				2
#define IMG_ARROW_LEFT				3
#define IMG_ARROW_RIGHT				4
#define IMG_ARROW_UP				5
#define IMG_BATTERY_0				6
#define IMG_BATTERY_1				7
#define IMG_BATTERY_2				8
#define IMG_BATTERY_3				9
#define IMG_BATTERY_CHARGING		10
#define IMG_BATTERY_LOW				11
#define IMG_BLUETOOTH				12
#define IMG_CALL					13
#define IMG_CALL_IN					14
#define IMG_CALL_OUT				15
#define IMG_CHECK					16
#define IMG_CHECKBOX_OFF			17
#define IMG_CHECKBOX_ON				18
#define IMG_DYNAMIC					19
#define IMG_DYNAMIC_OFF				20
#define IMG_DYNAMIC_ON				21
#define IMG_SIGNAL_1				22
#define IMG_SIGNAL_2				23
#define IMG_SIGNAL_3				24
#define IMG_SIGNAL_4				25
#define IMG_LIGHT					26
#define IMG_MELODY					27
#define IMG_SMS						28
#define IMG_NET_LEVEL_1				29
#define IMG_NET_LEVEL_2				30
#define IMG_NET_LEVEL_3				31
#define IMG_RADIO_OFF				32
#define IMG_RADIO_ON				33
#define IMG_SETTINGS				34
#define IMG_MESSAGE					35


void oledDrawBasicImg(uint8_t basic_img, uint8_t x, uint8_t y);


#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_BASIC_IMG_H_ */
