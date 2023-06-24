#include "oleg_basic.h"
#include "common.h"
#include "terminal_write.h"

uint8_t clear[1024] = {0x00};



void oled_display_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    oledInit();
    oledDrawCircle(25, 25, 15);
    oledDrawLine(0,30, 50, 0);

    oledFillSpace(20, 30);
    oledUpdatePic();

    while (true) {
		chThdSleepMilliseconds(50);
    }
}
