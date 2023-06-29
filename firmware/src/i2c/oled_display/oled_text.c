#include "oled_text.h"
#include "terminal_write.h"


static uint8_t font = FONT_6x9;
static uint8_t font_x = FONT_6x9_X;
static uint8_t font_y = FONT_6x9_Y;

bool oled_print_char(char symb, uint8_t x, uint8_t y){

}



void oledPrintText6x8(char *text, uint8_t x, uint8_t y){
	bool flagEndLine = false;
	for (uint8_t symb = 0; symb < strlen(text) && flagEndLine == false; symb++){
		if ((uint8_t) text[symb] < 32 || (uint8_t) text[symb] > 126) text[symb] = 127;
		for (uint8_t col = 0; col < FONT_6x8_COL; col++){
			if ((x + FONT_6x8_COL*symb + col) == OLED_LENGHT && flagEndLine == false) {
				flagEndLine = true;
				break;
			}
			for (uint8_t str = 0; str < FONT_6x8_STR; str++){
				if (y + str == OLED_HEIGHT) break;
				if (((font6x8GetElement(text[symb], col) >> str) & 0x01) == 1) {
					oledDrawPixel(x + col + symb * FONT_6x8_COL, y + str);
				}
			}
		}
	}
}


void oledPrintText12x16(char *text, uint8_t x, uint8_t y){
	bool flagEndLine = false;
	for (uint8_t symb = 0; symb < strlen(text) && flagEndLine == false; symb++){
		if ((uint8_t) text[symb] < 32 || (uint8_t) text[symb] > 126) text[symb] = 127;
		for (uint8_t part = 0; part < 2; part++){
			for (uint8_t col = 0; col < FONT_12x16_COL; col++){
				if ((x + FONT_12x16_COL*symb + col) == OLED_LENGHT && flagEndLine == false) {
					flagEndLine = true;
					break;
				}
				for (uint8_t str = 0; str < FONT_12x16_STR / 2; str++){
					if (y + str + part * 8 == OLED_HEIGHT) break;
					if (((font12x16GetElement(text[symb], col + part * FONT_12x16_COL) >> str) & 0x01) == 1) {
						oledDrawPixel(x + col + symb * FONT_12x16_COL, y + str + part * FONT_12x16_STR / 2);
					}
				}
			}
		}
	}
}

uint8_t oledPrintDigit6x8(uint8_t digit, uint8_t x, uint8_t y){
	char digit_ch[1] = "0";
	digit_ch[0] = (char) digit + 48;
	oledPrintText6x8(digit_ch, x, y);
	return (x + FONT_6x8_COL);
}

uint8_t oledPrintInteger6x8(int32_t integer, uint8_t x, uint8_t y){
	int16_t num = abs(integer);
	uint8_t num_of_digits = 0;
	char digit[] = "0";
	while (num != 0){
		num = num / 10;
		num_of_digits += 1;
	}
	if (integer < 0){
		digit[0] = 45;
		oledPrintText6x8(digit, x, y);
		x = x + FONT_6x8_COL;
		integer = abs(integer);
	}

	for (uint8_t i = 0; i < num_of_digits; i++){
		num = integer / ((uint16_t) pow(10, num_of_digits - i - 1));
		digit[0] = (char) num + 48;
		oledPrintText6x8(digit, x, y);
		integer = integer - num * (uint16_t) (pow(10, num_of_digits - i - 1));
		x += FONT_6x8_COL;
	}
	return x;
}

void oledPrintFloat6x8(float num, uint8_t num_after_point, uint8_t x, uint8_t y){
	int32_t num_temp;
	if (num_after_point != 0){
		if (num < 0) num_temp = ceil(num);
		else num_temp = floor(num);
		x = oledPrintInteger6x8(num_temp, x, y);

		oledPrintText6x8(".", x, y);
		x += FONT_6x8_COL;

		num = fabs(num) - abs(num_temp);
		for (uint8_t i = 0; i < num_after_point; i++){
			num *= 10;
			if (i + 1 == num_after_point) {
				num = roundf(num);
				if (num == 10) num -= 1;
			}
			num_temp = num;
			num -= num_temp;

			x = oledPrintDigit6x8(num_temp, x, y);
		}
	}
	else oledPrintInteger6x8((int32_t) roundf(num), x, y);

}

