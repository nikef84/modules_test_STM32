#include <common.h>


static inline void testRoutines(void) {
#if(PROGRAM_ROUTINE == LASER_RANGEFINDER)
    laser_rangefinder_test();
#elif(PROGRAM_ROUTINE == I2C)
    i2c_test();
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

