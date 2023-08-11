#include "buttons.h"


static thread_t *tp_motor;
static THD_WORKING_AREA(waMotor, 256);// 256 - stack size

static THD_FUNCTION(motorThread, arg)
{
    (void)arg; // just to avoid warnings
    chRegSetThreadName("Motor control thread");
    systime_t time = chVTGetSystemTime();
    while( !chThdShouldTerminateX() ){
      update_motor_voltage();
      time = chThdSleepUntilWindowed( time, time + TIME_MS2I( MOTOR_DATA_RATE ) );
    }
    chThdExit(MSG_OK);
}
