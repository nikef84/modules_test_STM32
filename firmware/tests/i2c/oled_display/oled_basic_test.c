#include "oled_basic_img.h"
#include "common.h"
#include "terminal_write.h"


void oled_basic_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled basic\r\n");
    oledInit();
    oledInvertColor(true);
    oledDrawBasicImg(IMG_ALARM, 10, 51);
    oledUpdatePic();
    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}
