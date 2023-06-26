#include "oled_geom.h"
#include "common.h"
#include "terminal_write.h"

uint8_t clear[1024] = {0x00};


void oled_display_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled\r\n");
    oledInit();
    oledDrawCircle(25, 25, 20, false);
    oledDrawLineCoord(25, 20, 25, 0);
    oledFillSpace(25, 25);
    oledUpdatePic();


    while (true) {
		chThdSleepMilliseconds(50);
    }
}
