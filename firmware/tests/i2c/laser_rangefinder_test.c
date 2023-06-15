#include "common.h"
#include "terminal_write.h"
#include "laser_rangefinder.h"



void laser_rangefinder_test(void){
    halInit();
    chSysInit();
    debugStreamInit();


    dbgPrintf("Start\r\n");
    chThdSleepMilliseconds(100);
    //i2cSimpleInit();

    lrInit();
    //dbgPrintf("%d\r\n", lrReadResult());
    chThdSleepMilliseconds(100);
    dbgPrintf("%d\r\n", lrRegisterRead(0x016));


//    dbgPrintf("%d\r\n", lrReadResult());
//            chThdSleepMilliseconds(200);
//

    while (true) {
    	dbgPrintf("%d\r\n", lrRegisterRead(0x004d));
//    	dbgPrintf("%d\r\n", lrReadResult());
		chThdSleepMilliseconds(50);
    }
}
