#include "snake.h"
#include "terminal_write.h"


void snake_test(void){
	halInit();
	chSysInit();
	debugStreamInit();
	dbgPrintf("Start snake\r\n");
	snakeInit();

	while (true) {
		snakeMove();
		oledUpdatePic();
		palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(1000);
	}
}
