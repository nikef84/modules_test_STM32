#include "common.h"
#include "terminal_write.h"
#include "i2c_lld.h"



void laser_rangefinder_test(void){
    halInit();
    chSysInit();
    uint8_t data = 2;

    debugStreamInit();
    i2cSimpleInit();
    chThdSleepMilliseconds(100);
    dbgPrintf("Start\r\n");
    msg_t msg = MSG_TIMEOUT;
    dbgPrintf("%d\r\n", msg);
    dbgPrintf("%d\r\n", i2cGetErrors(&I2CD1));
    while (true) {
        msg = i2cRegisterRead(DEVICE_LR, 0x016, &data, 1);

        chThdSleepMilliseconds(100);
		dbgPrintf("%d\t%d\r\n", data, msg);

    }
}

//void laser_rangefinder_test(void){
//    halInit();
//    chSysInit();
//    uint8_t data = 2;
//
//    debugStreamInit();
//    i2cDeviceInit(DEVICE_LR);
//    chThdSleepMilliseconds(100);
//    dbgPrintf("Start\r\n");
//    msg_t msg = MSG_TIMEOUT;
//    dbgPrintf("%d\r\n", msg);
//    dbgPrintf("%d\r\n", i2cGetErrors(&I2CD1));
//    while (true) {
//        msg = i2cRegisterRead(DEVICE_LR, 0x016, &data, 1);
//
//        chThdSleepMilliseconds(100);
//		dbgPrintf("%d\t%d\r\n", data, msg);
//
//    }
//}
