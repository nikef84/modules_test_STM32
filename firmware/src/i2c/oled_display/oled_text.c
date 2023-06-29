#include "oled_text.h"
#include "terminal_write.h"

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

