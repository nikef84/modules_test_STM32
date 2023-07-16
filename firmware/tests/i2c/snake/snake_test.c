#include "snake.h"
#include <stdlib.h>
#include "terminal_write.h"

uint8_t flag_but = 0;
void left_but(void* args){
    args = args;
    flag_but = 4;
}

void right_but(void* args){
    args = args;
    flag_but = 2;
}

void center_but(void* args){
    args = args;
    flag_but = 1;
}

void top_but(void* args){
    args = args;
    flag_but = 5;
}

void bottom_but(void* args){
    args = args;
    flag_but = 3;
}

void snake_test(void){
	halInit();
	chSysInit();
	debugStreamInit();

    palSetPadMode(GPIOC, 6, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, 6, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, 6, center_but, NULL);

    palSetPadMode(GPIOB, 15, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOB, 15, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOB, 15, right_but, NULL);

    palSetPadMode(GPIOB, 13, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOB, 13, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOB, 13, bottom_but, NULL);

    palSetPadMode(GPIOB, 12, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOB, 12, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOB, 12, left_but, NULL);

    palSetPadMode(GPIOC, 7, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, 7, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, 7, top_but, NULL);


	dbgPrintf("Start snake\r\n");
	snakeInit();

	while (true) {
		switch (flag_but){
		case 1:
			dbgPrintf("Center but\r\n");
			flag_but = 0;
			break;
		case 2:
			dbgPrintf("Right but\r\n");
			flag_but = 0;
			break;
		case 3:
			dbgPrintf("Bottom but\r\n");
			flag_but = 0;
			break;
		case 4:
			dbgPrintf("Left but\r\n");
			flag_but = 0;
			break;
		case 5:
			dbgPrintf("Top but\r\n");
			flag_but = 0;
			break;
		default:
			break;
		}
//		snakeGame();
//		oledUpdatePic();
		palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(300);
	}
}
