#include "common.h"
#include "terminal_write.h"
#include "led_matrix.h"



void led_matrix_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start led matrix\r\n");
    i2cSimpleInit();
    chThdSleepMilliseconds(100);
    uint8_t buf[2] = {0x00, 0x00};
    i2cSimpleWrite(LM_ADDRESS, buf, 2);
    chThdSleepMilliseconds(100);
    msg_t msg = MSG_OK;
    uint8_t tx[2] = {0x02, 0x03};
    msg = i2cSimpleWrite(LM_ADDRESS, tx, 2);
    chThdSleepMilliseconds(100);
	dbgPrintf("msg = %d\t err = %d\r\n", msg, i2cGetErrors(&I2CD1));

    while (true) {
    	palToggleLine(LINE_LED3);
    	chThdSleepMilliseconds(100);
    }
}
