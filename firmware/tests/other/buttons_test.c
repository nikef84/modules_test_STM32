#include "buttons.h"
#include "terminal_write.h"



void button_test(void){
	halInit();
	chSysInit();
	debugStreamInit();
	buttonsInit();

	dbgPrintf("Start buttons\r\n");
	while (true) {
		if(buttonsGetFlagNewVal() == true){
			switch ((uint8_t)buttonsGetCurrentBut()){
			case CENTER:
				dbgPrintf("Center\r\n");
				break;
			case LEFT:
				dbgPrintf("Left\r\n");
				break;
			case RIGHT:
				dbgPrintf("Right\r\n");
				break;
			case TOP:
				dbgPrintf("Top\r\n");
				break;
			case BOTTOM:
				dbgPrintf("Bottom\r\n");
				break;
			}
		}

		palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(300);
	}
}
