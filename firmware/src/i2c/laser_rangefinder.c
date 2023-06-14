#include "laser_rangefinder.h"

void lrInit(void){
	i2cSimpleInit();
	i2cRegisterRead(LR_ADDRESS, register_addr, rxbuf, length)
}
