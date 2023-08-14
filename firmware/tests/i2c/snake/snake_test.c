#include "snake.h"
#include <stdlib.h>
#include "terminal_write.h"


void snake_test(void){
	halInit();
	chSysInit();
	debugStreamInit();

	dbgPrintf("Start snake\r\n");
	snakeInit();

	while (true) {
		snakeGame();
		oledUpdatePic();
		palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(300);
	}
}
