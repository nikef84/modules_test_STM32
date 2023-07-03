#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_

#include "oled_basic.h"
#include "oled_fonts.h"
#include "string.h"
#include "math.h"


// Add it to convert the digit to the digit char.
#define DIGIT_TO_CHAR	48



/*
 * @brief	Displays text on the display.
 *
 * @note	Depends on current font.
 *
 * @param_in	text	An array of chars, which will be displayed. (
 * 				x		Horizontal pixel number.
 * 				y		Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @param_out	x		Horizontal pixel number for new symbol.
 */
uint8_t oledPrintText(char *text, uint8_t x, uint8_t y);


/*
 * @brief	Displays the digit to the screen.
 *
 * @note	Depends on current font.
 *
 * @param_in	digit	Digit (from 0 to 9), which will be displayed.
 * 				x		Horizontal pixel number.
 * 				y		Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @param_out	x		Horizontal pixel number for new symbol.
 */
uint8_t oledPrintDigit(uint8_t digit, uint8_t x, uint8_t y);


/*
 * @brief	Displays the integer to the screen.
 *
 * @note	Depends on current font.
 *
 * @param_in	integer		Integer, which will be displayed (can be both:pos or neg).
 * 				x			Horizontal pixel number.
 * 				y			Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @param_out	x		Horizontal pixel number for new symbol.
 */
uint8_t oledPrintInteger(int32_t integer, uint8_t x, uint8_t y);


/*
 * @brief	Displays the float to the screen.
 *
 * @note	Depends on current font.
 *
 * @note	Round the answer.
 *
 * @param_in	num					A float, which will be displayed.
 * 				num_after_point		The number of digits after the decimal point.
 * 				x					Horizontal pixel number.
 * 				y					Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @param_out	x		Horizontal pixel number for new symbol.
 */
uint8_t oledPrintFloat(float num, uint8_t num_after_point, uint8_t x, uint8_t y);


/*
 * @brief	Set a font of drawing.
 *
 * @note	The size of font is in pixels.
 *
 * @note	Can be: FONT6x8
 * 					FONT_12x16
 *
 * @param_in	new_font	New font of drawing.
 */
void oledSetFont(uint8_t new_font);


/*
 * @brief	Get current font.
 *
 * @note	Can be: FONT6x8
 * 					FONT_12x16
 *
 * @param_out	font	Current font of drawing.
 */
uint8_t oledGetFont(void);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_TEXT_H_ */
