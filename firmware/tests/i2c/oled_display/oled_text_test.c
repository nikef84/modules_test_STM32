#include "oled_text.h"
#include "common.h"
#include "terminal_write.h"



void oled_text_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled text\r\n");
    oledInit();
    char c[] = "gleb";
    oledPrintText12x16(c, 10, 10);
    oledUpdatePic();


    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}
