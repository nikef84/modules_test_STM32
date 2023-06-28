#include "oled_geom.h"
#include "common.h"
#include "terminal_write.h"

void fill_diff_space(void);



void oled_display_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled\r\n");
    oledInit();
    oledDrawCircle(10, 10, 30, false);
    oledFillSpace(10, 10);
    oledUpdatePic();

    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}


void fill_diff_space(void){
	oledDrawCircle(25, 25, 10, false);
	oledSetColorDraw(COLOR_BLACK);
	oledDrawRect(15, 25, 35, 35, true);
	oledSetColorDraw(COLOR_WHITE);
	oledDrawLineCoord(15, 25, 15, 50);
	oledDrawLineCoord(15, 50, 100, 50);
	oledDrawLineCoord(100, 50, 100, 10);
	oledDrawLineCoord(100, 10, 40, 10);
	oledDrawLineCoord(40, 10, 40, 20);
	oledDrawLineCoord(40, 20, 45, 20);
	oledDrawLineCoord(45, 20, 45, 13);
	oledDrawLineCoord(45, 13, 60, 20);
	oledDrawLineCoord(60, 20, 40, 30);
	oledDrawLineCoord(40, 30, 35, 25);
	oledDrawCircle(25, 25, 5, false);
	oledUpdatePic();
	oledFillSpace(60, 30);
	oledUpdatePic();
}
