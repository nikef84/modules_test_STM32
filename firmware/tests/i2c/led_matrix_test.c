#include "common.h"
#include "led_matrix.h"


static bool flag = false;

void palcb_button(void* args){
    args = args;
    flag = true;
}

// Use the button to change the picture.
void led_matrix_test(void){
    halInit();
    chSysInit();
    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, palcb_button, NULL);
    lmInit();
    chThdSleepMilliseconds(100);
    lmPicHeart();
    bool picture = true;
    while (true) {
    	if (flag == true){
    		if (picture == true) {
    			picture = false;
    			lmPicSkull();
    		}
    		else {
    			picture = true;
				lmPicHeart();
    		}
    		flag = false;
    	}
    	lmGradientBrightness();

    	chThdSleepMilliseconds(100);
    }
}
