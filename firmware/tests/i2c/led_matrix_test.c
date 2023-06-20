#include "common.h"
#include "terminal_write.h"
#include "led_matrix.h"



void led_matrix_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    i2cSimpleInit();
    chThdSleepMilliseconds(100);
    //uint8_t buf[2] = {0x00, 0x00};
    //i2cSimpleWrite(LM_ADDRESS, buf, 2);
    chThdSleepMilliseconds(100);
    uint8_t tx[1] = {0x00};
    uint8_t rx[1]  ={0x02};
    msg_t msg = MSG_OK;


    while (true) {
    	palToggleLine(LINE_LED3);
    	msg = i2cMasterTransmitTimeout(&I2CD1, LM_ADDRESS, tx, 1, rx, 1, 1000);
    	dbgPrintf("msg = %d\t err = %d\r\n", msg, i2cGetErrors(&I2CD1));
    	chThdSleepMilliseconds(100);
    }
}
