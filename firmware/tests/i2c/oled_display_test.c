#include "common.h"
#include "terminal_write.h"
#include "oled_display.h"

uint8_t clear[1024] = {0x00};



void oled_display_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    oledInit();
    oledDrawCircle(50, 20, 20);
    oledUpdatePic();




//    for (uint8_t i = 0; i != 32; i++){
//        oledRegisterWriteSix(0x22, 0, 7);
//    	oledRegisterWriteSix(0x21, i*4, (i+1)*4 - 1);
//        uint8_t tx[9] = {0x40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//        i2cSimpleWrite(OLED_ADDR, tx, 9);
//    }

    while (true) {
		chThdSleepMilliseconds(50);
    }
}
