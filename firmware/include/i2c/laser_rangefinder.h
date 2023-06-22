#ifndef INCLUDE_I2C_LASER_RANGEFINDER_H_
#define INCLUDE_I2C_LASER_RANGEFINDER_H_

#include "i2c_lld.h"

// Address of the laser rangefinder VL6180X. LR - laser rengefinder.
#define LR_ADDRESS						0b0101001

// Possible operating modes.
#define ONE_SHOT_MODE					0
#define CONTINUOUS_MODE					1

// The current operating mode.
#define LR_MODE							CONTINUOUS_MODE


/*
 * @brief 	Inits I2C and sets the settings to the rangefinder sensor.
 *
 * @note I2CD1 is used.
 */
void lrInit(void);

/*
 * @brief	Writes the data to the rangefinder sensor.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 2 bytes!
 *
 * 				data 			The information we want to write to the selected register.
 * 								Must be 1 byte!
 */
void lrRegisterWrite(uint16_t reg_address, uint8_t data);

/*
 * @brief	Reads the data in the register from the rangefinder sensor.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 2 bytes!
 *
 * param_out	data			The data that is stored in the register.
 */
uint8_t lrRegisterRead(uint16_t reg_address);

/*
 * @brief	Reads the range from the rangefinder sensor.
 *
 * param_out	data			The range from the sensor to the object. (1 byte)
 *								The result is equal to the range in mm.
 */
uint8_t lrReadResult(void);


#endif /* INCLUDE_I2C_LASER_RANGEFINDER_H_ */
