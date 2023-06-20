#include "common.h"
#include "terminal_write.h"
#include "laser_rangefinder.h"


void i2c_test(void){
    halInit();
    chSysInit();
    uint8_t data = 2;

    debugStreamInit();
    i2cSimpleInit();
    chThdSleepMilliseconds(100);
    dbgPrintf("Start\r\n");
    msg_t msg = MSG_TIMEOUT;
    //msg = i2cRegisterRead(LR_ADDRESS, 0x000, &data, 1);
    while (true) {


        chThdSleepMilliseconds(100);
		dbgPrintf("%d\t%d\r\n", data, msg);

    }
}
