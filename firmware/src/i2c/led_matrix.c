#include "led_matrix.h"

void lmInit(void){
	i2cSimpleInit();
}

/*
 * @brief	Writes the data to the rangefinder sensor.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 2 bytes!
 *
 * 				data 			The information we want to write to the selected register.
 * 								Must be 1 byte!
 */
void lmRegisterWrite(uint8_t reg_address, uint8_t data){
	uint8_t txbuf[2] = {reg_address, data};
	i2cSimpleWrite(LM_ADDRESS, txbuf, 2);
	chThdSleepMilliseconds(10);
}
//
///*
// * @brief	Reads the data in the register from the rangefinder sensor.
// *
// * @param_in	reg_address 	The address of the register to which we want to write information.
// * 							  	Must be 2 bytes!
// *
// * param_out	data			The data that is stored in the register.
// */
//uint8_t lrRegisterRead(uint16_t reg_address){
//	uint8_t txbuf[2] = {(reg_address >> 8) & 0xFF, reg_address};
//	uint8_t data = 0;
//	msg_error = i2cRegisterRead(LR_ADDRESS, txbuf, 2, &data, 1);
//	chThdSleepMilliseconds(10);
//	return data;
//}
//
///*
// * @brief	Clears the interrupts.
// *
// * @notapi
// */
//void lr_clear_interrupts(void) {
//	lrRegisterWrite(0x015,0x07);
//}
//
///*
// * @brief	Reads the range from the rangefinder sensor.
// *
// * param_out	data			The range from the sensor to the object. (1 byte)
// *								The result is equal to the range in mm.
// */
//uint8_t lrReadResult(void){
//	if (LR_MODE == ONE_SHOT_MODE)lrRegisterWrite(0x0018, 0x01);
//	uint8_t res = lrRegisterRead(0x062);
//	lr_clear_interrupts();
//	return res;
//}
