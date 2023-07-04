#include "oled_basic_img.h"
#include "common.h"
#include "terminal_write.h"






void oled_basic_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled basic\r\n");
    oledInit();
//    uint8_t buf[3] = {0x00, 0xBB, 0x00};
//    shift_down(buf, 3, 3);
//    dbgPrintf("%d\t%d\t%d\r\n", buf[0], buf[1], buf[2]);
    oledInvertColor(true);
    oledDrawBasicImg(IMG_ALARM, 10, 51);
    oledUpdatePic();
    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}
