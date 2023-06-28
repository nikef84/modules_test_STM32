#include "oled_text.h"
#include "common.h"
#include "terminal_write.h"

//void oledPrintText6x8(char *text, uint8_t x, uint8_t y){
//	bool flagEndLine = false;
//	for (uint8_t symb = 0; symb < strlen(text) && flagEndLine == false; symb++){
//		for (uint8_t col = 0; col < FONT_6x8_COL; col++){
//			if ((x + FONT_6x8_COL*symb + col) == OLED_LENGHT && flagEndLine == false) {
//				flagEndLine = true;
//				break;
//			}
//			for (uint8_t str = 0; str < FONT_6x8_STR; str++){
//				if (y + str == OLED_HEIGHT) break;
//				if (((oled_font_6x8[((text[symb] - FONT_DIFF) * FONT_6x8_COL) + col] >> str) & 0x01) == 1) {
//					oledDrawPixel(x + col, y + str);
//				}
//			}
//		}
//	}
//}

void oled_text_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled text\r\n");
    oledInit();
    char c[] = "423 len";
    //oledPrintText6x8(c, 10, 10);
    oledUpdatePic();


    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}
