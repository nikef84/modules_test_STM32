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
    dbgPrintf("OLED_BYTES_PER_COLOM = %d\r\n", OLED_BYTES_PER_COLOM);
    dbgPrintf("OLED_PIC_BUF_SIZE = %d\r\n", OLED_PIC_BUF_SIZE);

    dbgPrintf("OLED_BUF_SEPARATOR = %d\r\n", OLED_BUF_SEPARATOR);

    dbgPrintf("OLED_SEPAR_BUF_SIZE = %d\r\n", OLED_SEPAR_BUF_SIZE);

    oledDrawLineCoord(10, 10, 100, 10);
    oledUpdatePic();

    while (true) {
		chThdSleepMilliseconds(50);
    }
}
