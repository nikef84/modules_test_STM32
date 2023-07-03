#include "oled_text.h"
#include "common.h"
#include "terminal_write.h"



void oled_text_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled text\r\n");
    oledInit();
    oledSetFont(FONT_12x16);
    oledPrintFloat(22146.51, 2, 10, 10);
    oledUpdatePic();


    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}
