#include "oled_animation_cat.h"
#include "common.h"
#include "terminal_write.h"


void oled_animation_cat_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled animation_cat\r\n");
    oledInit();
    oledInvertColor(true);

    while (true) {
    	oledClearBuf();
    	oledDrawAnimationCat();
		oledUpdatePic();
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(50);
    }
}
