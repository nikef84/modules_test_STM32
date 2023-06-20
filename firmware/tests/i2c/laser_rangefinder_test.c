#include "common.h"
#include "terminal_write.h"
#include "laser_rangefinder.h"



void laser_rangefinder_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    lrInit();
    chThdSleepMilliseconds(100);
    while (true) {
    	dbgPrintf("%d\r\n", lrReadResult());
		chThdSleepMilliseconds(50);
    }
}
