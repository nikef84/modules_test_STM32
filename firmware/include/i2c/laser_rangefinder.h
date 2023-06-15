#ifndef INCLUDE_I2C_LASER_RANGEFINDER_H_
#define INCLUDE_I2C_LASER_RANGEFINDER_H_

#include "i2c_lld.h"


#define LR_ADDRESS						0b0101001

#define REG_SET_SETTINGS				0x016



#define MODE_START_SET_SETTINGS			0x01
#define MODE_STOP_SET_SETTINGS			0x00

#define ONE_SHOT_MODE					0
#define CONTINUOUS_MODE					1
#define LR_MODE							CONTINUOUS_MODE

void lrInit(void);
void lrRegisterWrite(uint16_t reg_address, uint8_t data);
uint8_t lrRegisterRead(uint16_t reg_address);
uint8_t lrReadResult(void);

#endif /* INCLUDE_I2C_LASER_RANGEFINDER_H_ */
