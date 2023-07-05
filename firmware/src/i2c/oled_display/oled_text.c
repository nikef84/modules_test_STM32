#include "oled_text.h"
#include "terminal_write.h"

// Characteristics of the font in which the text will be displayed.
static uint8_t font = FONT_6x8; // Font type.
static uint8_t font_x = FONT_6x8_X; // Horizontal lenght in pixels.
static uint8_t font_y = FONT_6x8_Y; // Vertical lenght in pixels.


/*
 * @brief	Displays a char on the screen.
 *
 * @note	Depends on current font.
 *
 * @param_in	symb	A char, which will be displayed.
 * 				x		Horizontal pixel number.
 * 				y		Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @param_out	flagEndLine		x is out of drawing range.
 *
 * @notapi
 */
bool oled_print_char(char symb, uint8_t x, uint8_t y){
	uint16_t colom[font_y]; // Contains pixels of the char.
	bool flagEndLine = false; // x is out of drawing range.

	if ((uint8_t) symb < SYMB_MIN || (uint8_t) symb > SYMB_MAX - 1) symb = SYMB_MAX; // ACKII table check.
	// Depends on the current font.
	if (font == FONT_6x8){
		for (uint8_t i = 0; i < font_x; i++){
			colom[i] = font6x8GetElement(symb, i);
		}
	}
	else if (font == FONT_12x16){
		for (uint8_t i = 0; i < font_x; i++){
			colom[i] = font12x16GetElement(symb, i) | (uint16_t) (font12x16GetElement(symb, FONT_12x16_X + i) << 8);
		}
	}
	// Print the char.
	for (uint8_t col = 0; col < font_x; col++){
		if ((x + col) == OLED_LENGHT && flagEndLine == false) { // x is out of drawing range.
			flagEndLine = true;
			break;
		}
		for (uint8_t str = 0; str < font_y; str++){
			if (y + str == OLED_HEIGHT) break; // y is out of drawing range.
			if (((colom[col] >> str) & 0x01) == 1) {
				oledDrawPixel(x + col, y + str);
			}
		}
	}
	return flagEndLine;
}


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
uint8_t oledPrintText(char *text, uint8_t x, uint8_t y){
	bool flagEndLine = false;

	for (uint8_t symb = 0; symb < strlen(text) && flagEndLine == false; symb++){
		flagEndLine = oled_print_char(text[symb], x, y);
		x = x + font_x;
	}
	return x;
}


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
uint8_t oledPrintDigit(uint8_t digit, uint8_t x, uint8_t y){
	char digit_ch[1] = "0";
	if (digit / 10 < 1){ // Checks if it is a digit.
		digit_ch[0] = (char) digit + DIGIT_TO_CHAR;
		oled_print_char(digit_ch[0], x, y);
		x += font_x;
	}
	return x;
}


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
uint8_t oledPrintInteger(int32_t integer, uint8_t x, uint8_t y){
	int16_t num = abs(integer);
	uint8_t num_of_digits = 0;

	while (num != 0){ // Counts digits in the integer.
		num = num / 10;
		num_of_digits += 1;
	}

	if (integer < 0){ // Print the minus if the integer is negative.
		oledPrintText("-", x, y);
		x += font_x;
		integer = abs(integer);
	}

	// Print the integer.
	for (uint8_t i = 0; i < num_of_digits; i++){
		num = integer / ((uint16_t) pow(10, num_of_digits - i - 1));
		oledPrintDigit(num, x, y);
		integer = integer - num * (uint16_t) (pow(10, num_of_digits - i - 1));
		x += font_x;
	}
	return x;
}


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
uint8_t oledPrintFloat(float num, uint8_t num_after_point, uint8_t x, uint8_t y){
	int32_t num_temp;

	if (num_after_point != 0){ // To round the answer.
		// The integer part of a fractional number.
		if (num < 0) num_temp = ceil(num);
		else num_temp = floor(num);
		x = oledPrintInteger(num_temp, x, y);

		// Print decimal point.
		oledPrintText(".", x, y);
		x += font_x;

		// The fractional part of a fractional number.
		num = fabs(num) - abs(num_temp);
		for (uint8_t i = 0; i < num_after_point - 1; i++){
			num *= 10;
			num_temp = (int32_t) num;
			num -= (float) num_temp;

			x = oledPrintDigit(num_temp, x, y);
		}
		// Round the answer.
		num *= 10;
		num = roundf(num);
		if (num == 10) num -= 1;
		num_temp = (int32_t) num;
		x = oledPrintDigit(num_temp, x, y);
	}
	else x = oledPrintInteger((int32_t) roundf(num), x, y); // To round the integer part.

	return x;
}


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
void oledSetFont(uint8_t new_font){
	switch (new_font){
	case FONT_12x16:
		font = FONT_12x16;
		font_x = FONT_12x16_X;
		font_y = FONT_12x16_Y;
		break;
	case FONT_6x8:
		font = FONT_6x8;
		font_x = FONT_6x8_X;
		font_y = FONT_6x8_Y;
		break;
	default:
		break;
	}
}


/*
 * @brief	Get current font.
 *
 * @note	Can be: FONT6x8
 * 					FONT_12x16
 *
 * @param_out	font	Current font of drawing.
 */
uint8_t oledGetFont(void){
	return font;
}

