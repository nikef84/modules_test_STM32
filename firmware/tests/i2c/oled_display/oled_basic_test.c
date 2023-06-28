#include "oled_geom.h"
#include "common.h"
#include "terminal_write.h"


void oled_display_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled\r\n");
    oledInit();
//    oledDrawLineCoord(0, 0, 127, 63);
    oledUpdatePic();
//    chThdSleepMilliseconds(50);
//    dbgPrintf("111\r\n");
//    chThdSleepMilliseconds(500);
//    //oledDrawLineCoord(25, 20, 25, 0);
//    oledFillV2(25, 25);
//    oledUpdatePic();


    while (true) {
    	dbgPrintf("11\r\n");
		chThdSleepMilliseconds(50);
    }
}
