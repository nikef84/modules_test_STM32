#include "oled_basic_img.h"
#include "common.h"
#include "terminal_write.h"


void oled_basic_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start oled basic\r\n");
    oledInit();
    oledInvertColor(true);

    oledDrawBasicImg(IMG_ARROW_DOWN, 0, 0);
    oledDrawBasicImg(IMG_ARROW_LEFT, 15, 0);
    oledDrawBasicImg(IMG_ARROW_RIGHT, 30, 0);
    oledDrawBasicImg(IMG_ARROW_UP, 45, 0);
    oledDrawBasicImg(IMG_BLUETOOTH, 60, 0);
    oledDrawBasicImg(IMG_CHECKBOX_OFF, 75, 0);
    oledDrawBasicImg(IMG_CHECKBOX_ON, 90, 0);
    oledDrawBasicImg(IMG_CHECK, 105, 0);

    oledDrawBasicImg(IMG_BATTERY_0, 0, 10);
    oledDrawBasicImg(IMG_BATTERY_1, 20, 10);
    oledDrawBasicImg(IMG_BATTERY_2, 40, 10);
    oledDrawBasicImg(IMG_BATTERY_3, 60, 10);
    oledDrawBasicImg(IMG_BATTERY_CHARGING, 80, 10);
    oledDrawBasicImg(IMG_BATTERY_LOW, 100, 10);

    oledDrawBasicImg(IMG_CALL, 0, 20);
    oledDrawBasicImg(IMG_CALL_IN, 20, 20);
    oledDrawBasicImg(IMG_CALL_OUT, 40, 20);
    oledDrawBasicImg(IMG_SIGNAL_1, 60, 20);
    oledDrawBasicImg(IMG_SIGNAL_2, 80, 20);
    oledDrawBasicImg(IMG_SIGNAL_3, 100, 20);
    oledDrawBasicImg(IMG_SIGNAL_4, 115, 20);

    oledDrawBasicImg(IMG_DYNAMIC, 0, 30);
    oledDrawBasicImg(IMG_DYNAMIC_OFF, 20, 30);
    oledDrawBasicImg(IMG_DYNAMIC_ON, 40, 30);
    oledDrawBasicImg(IMG_HEART, 60, 30);

    oledDrawBasicImg(IMG_SMS, 0, 40);
    oledDrawBasicImg(IMG_NET_LEVEL_1, 15, 40);
    oledDrawBasicImg(IMG_NET_LEVEL_2, 30, 40);
    oledDrawBasicImg(IMG_NET_LEVEL_3, 45, 40);
    oledDrawBasicImg(IMG_ALARM, 60, 40);

    oledDrawBasicImg(IMG_RADIO_OFF, 0, 50);
    oledDrawBasicImg(IMG_RADIO_ON, 15, 50);
    oledDrawBasicImg(IMG_SETTINGS, 30, 50);
    oledDrawBasicImg(IMG_LIGHT, 45, 50);
    oledDrawBasicImg(IMG_MELODY, 60, 50);

    oledDrawBasicImg(IMG_MESSAGE, 80, 30);
    oledUpdatePic();
    while (true) {
    	palToggleLine(LINE_LED3);
		chThdSleepMilliseconds(500);
    }
}
