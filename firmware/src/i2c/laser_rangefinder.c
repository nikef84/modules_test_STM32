#include "laser_rangefinder.h"

msg_t msg_error = MSG_OK;

/*
 * @brief 	Contains recomended privit and public settings.
 *
 * @note	Below are the recommended settings required to be loaded onto
 * 			the VL6180X during the initialisation of the device.
 *
 * @note	The program works with this configuration. PLS, DO NOT TOUCH! :)
 *
 * @notapi
 */
void set_init_setting(void){
	// Private registers.
	lrRegisterWrite(0x0207, 0x01);
	lrRegisterWrite(0x0208, 0x01);
	lrRegisterWrite(0x0096, 0x00);
	lrRegisterWrite(0x0097, 0xfd);
	lrRegisterWrite(0x00e3, 0x00);
	lrRegisterWrite(0x00e4, 0x04);
	lrRegisterWrite(0x00e5, 0x02);
	lrRegisterWrite(0x00e6, 0x01);
	lrRegisterWrite(0x00e7, 0x03);
	lrRegisterWrite(0x00f5, 0x02);
	lrRegisterWrite(0x00d9, 0x05);
	lrRegisterWrite(0x00db, 0xce);
	lrRegisterWrite(0x00dc, 0x03);
	lrRegisterWrite(0x00dd, 0xf8);
	lrRegisterWrite(0x009f, 0x00);
	lrRegisterWrite(0x00a3, 0x3c);
	lrRegisterWrite(0x00b7, 0x00);
	lrRegisterWrite(0x00bb, 0x3c);
	lrRegisterWrite(0x00b2, 0x09);
	lrRegisterWrite(0x00ca, 0x09);
	lrRegisterWrite(0x0198, 0x01);
	lrRegisterWrite(0x01b0, 0x17);
	lrRegisterWrite(0x01ad, 0x00);
	lrRegisterWrite(0x00ff, 0x05);
	lrRegisterWrite(0x0100, 0x05);
	lrRegisterWrite(0x0199, 0x05);
	lrRegisterWrite(0x01a6, 0x1b);
	lrRegisterWrite(0x01ac, 0x3e);
	lrRegisterWrite(0x01a7, 0x1f);
	lrRegisterWrite(0x0030, 0x00);

	lrRegisterWrite(0x016, 0x00);

	// Public registers.

	lrRegisterWrite(0x001b, 0x09);
	lrRegisterWrite(0x0031, 0xFF);
	lrRegisterWrite(0x002e, 0x01);

	lrRegisterWrite(0x001c, 0x32);
	lrRegisterWrite(0x002d, 0x10 | 0x01);

	lrRegisterWrite(0x0022, 0x00);
	lrRegisterWrite(0x0022 + 1, 0x7B);

	lrRegisterWrite(0x003e, 0x0A);

	lrRegisterWrite(0x003e + 1, 0x63);

	lrRegisterWrite(0x010a, 0x30);

	lrRegisterWrite(0x003f, 0x46);

	lrRegisterWrite(0x0120, 0x01);

	// Configure the interrupts
	lrRegisterWrite(0x0010, 0x00);
	lrRegisterWrite(0x0011, 0x30);
	lrRegisterWrite(0x0014, 0x24);

	// enable continuous range mode
	if (LR_MODE == CONTINUOUS_MODE){
		lrRegisterWrite(0x0018, 0x03);
	}
}

/*
 * @brief 	Inits I2C and sets the settings to the rangefinder sensor.
 *
 * @note I2CD1 is used.
 */
void lrInit(void){
	i2cSimpleInit();

	uint8_t mode = lrRegisterRead(0x0016);
	//  if that bit set, then device has been freshly initialized.
	if (mode == 0x01){
		set_init_setting();
	}

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
void lrRegisterWrite(uint16_t reg_address, uint8_t data){
	uint8_t txbuf[3] = {(reg_address >> 8) & 0xFF, reg_address, data};
	msg_error = i2cSimpleWrite(LR_ADDRESS, txbuf, 3);
	chThdSleepMilliseconds(10);
}

/*
 * @brief	Reads the data in the register from the rangefinder sensor.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 2 bytes!
 *
 * param_out	data			The data that is stored in the register.
 */
uint8_t lrRegisterRead(uint16_t reg_address){
	uint8_t txbuf[2] = {(reg_address >> 8) & 0xFF, reg_address};
	uint8_t data = 0;
	msg_error = i2cRegisterRead(LR_ADDRESS, txbuf, 2, &data, 1);
	chThdSleepMilliseconds(10);
	return data;
}

/*
 * @brief	Clears the interrupts.
 *
 * @notapi
 */
void lr_clear_interrupts(void) {
	lrRegisterWrite(0x015,0x07);
}

/*
 * @brief	Reads the range from the rangefinder sensor.
 *
 * param_out	data			The range from the sensor to the object. (1 byte)
 *								The result is equal to the range in mm.
 */
uint8_t lrReadResult(void){
	if (LR_MODE == ONE_SHOT_MODE)lrRegisterWrite(0x0018, 0x01);
	uint8_t res = lrRegisterRead(0x062);
	lr_clear_interrupts();
	return res;
}
