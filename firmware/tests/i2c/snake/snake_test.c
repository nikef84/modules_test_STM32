#include "snake.h"
#include <stdlib.h>
#include "terminal_write.h"


void snake_test(void){
	halInit();
	chSysInit();
	debugStreamInit();

	dbgPrintf("Start snake\r\n");
	snakeInit();

	systime_t time = chVTGetSystemTime();
	while (true) {

		systime_t time1 = chVTGetSystemTime();
		snakeGame();


		oledUpdatePic();
		palToggleLine(LINE_LED3);
		time = chThdSleepUntilWindowed( time, time + TIME_MS2I( SNAKE_GAME_PERIOD ) );
		dbgPrintf("%d\r\n", chVTGetSystemTime() - time1);

	}
}
