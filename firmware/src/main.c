#include <common.h>


static inline void testRoutines(void) {
#if(PROGRAM_ROUTINE == LASER_RANGEFINDER)
    laser_rangefinder_test();
#elif(PROGRAM_ROUTINE == I2C)
    i2c_test();
#elif(PROGRAM_ROUTINE == LED_MATRIX)
    led_matrix_test();
#elif(PROGRAM_ROUTINE == OLED_GEOM)
    oled_geom_test();
#elif(PROGRAM_ROUTINE == OLED_TEXT)
    oled_text_test();
#endif
}



int main(void) {
#if(PROGRAM_ROUTINE != MAIN_ROUTINE)
    testRoutines();

#else
    chSysInit();
    halInit();

    while(1);

#endif
}

