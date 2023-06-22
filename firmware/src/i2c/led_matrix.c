#include "led_matrix.h"

// Just for clear the led matrix.
static uint8_t pic_clear[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Picture of the heart.
static uint8_t pic_heart[8] = {0b00000000,
							   0b01100110,
							   0b11111111,
							   0b11111111,
							   0b11111111,
							   0b01111110,
							   0b00111100,
							   0b00011000};

// Pucture of the skull.
static uint8_t pic_skull[8] = {0b01111110,
							   0b11111111,
							   0b10111101,
							   0b10011001,
							   0b11111111,
							   0b11100111,
							   0b01111110,
							   0b01011010};

// Just for control the brightness gradient.
static uint8_t brightness_current = 0; // Current value of brightness.
static int8_t  brightness_direction = 1;
// Must be from 0x08 to 0x0C, because of the current.
static uint8_t brightness_buf[5] = {BRIGHTNESS_2, BRIGHTNESS_4, BRIGHTNESS_6, BRIGHTNESS_8, BRIGHTNESS_10};

/*
 * @brief 	Inits I2C and sets the settings to the led matrix.
 *
 * @note I2CD1 is used.
 */
void lmInit(void){
	i2cSimpleInit(); // Inits I2C.
	lmRegisterWrite(REG_SETTINGS, INIT_SETTINGS); // Sets initial settings.
	lmRegisterWrite(REG_BRIGHTNESS, BRIGHTNESS_10); // Sets highest britness.
	lmClearPic(); // Clear the led matrix.
}

/*
 * @brief	Writes the data to the led matrix.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 1 byte!
 *
 * 				data 			The information we want to write to the selected register.
 * 								Must be 1 byte!
 */
void lmRegisterWrite(uint8_t reg_address, uint8_t data){
	uint8_t txbuf[2] = {reg_address, data};
	i2cSimpleWrite(LM_ADDRESS, txbuf, 2);
	chThdSleepMilliseconds(10);
}

/*
 * @brief	Displays the picture on the led matrix.
 *
 * @param_in	picture		1D array in which each elemet is a string of led matrix.
 * 							Must consist of 8 elements.
 */
void lmSetPicture(uint8_t *picture){
	lmRegisterWrite(REG_LINE_1, picture[0]);
	lmRegisterWrite(REG_LINE_2, picture[1]);
	lmRegisterWrite(REG_LINE_3, picture[2]);
	lmRegisterWrite(REG_LINE_4, picture[3]);
	lmRegisterWrite(REG_LINE_5, picture[4]);
	lmRegisterWrite(REG_LINE_6, picture[5]);
	lmRegisterWrite(REG_LINE_7, picture[6]);
	lmRegisterWrite(REG_LINE_8, picture[7]);
	lmRegisterWrite(REG_CONFIRM_PIC, 0x01); // Doesn't matter what to write.
}

/*
 * @brief	Clears the led matrix.
 */
void lmClearPic(void){
	lmSetPicture(pic_clear);
}

/*
 * @brief	Displays the picture of the heart to the led matrix.
 *
 * @note	00000000
 *		   	01100110
 *		  	11111111
 *	   		11111111
 *	   		11111111
 *	   		01111110
 *	   		00111100
 *	   		00011000
 */
void lmPicHeart(void){
	lmSetPicture(pic_heart);
}

/*
 * @brief	Displays the picture of the skull to the led matrix.
 *
 * @note	01111110
 *			11111111
*			10111101
 *			10011001
 *			11111111
 *			11100111
 *			01111110
 *			01011010
 */
void lmPicSkull(void){
	lmSetPicture(pic_skull);
}

/*
 * @brief	Change the brightness of the led matrix.
 *
 * @param_in	brightness	The new value of brightness.
 * 							Must be from 0x08 to 0x0C, because of the current.
 */
void lmChangeBrightness(uint8_t brightness){
	lmRegisterWrite(REG_BRIGHTNESS, brightness);
}

/*
 * @brief	Change the brightness of the led matrix gradually.
 *
 * @note 	Use it in a loop.
 */
void lmGradientBrightness(void){
	lmChangeBrightness(brightness_buf[brightness_current]);
	if (brightness_current == 0) brightness_direction = 1;
	else if (brightness_current == 4) brightness_direction = -1;
	brightness_current = brightness_current + brightness_direction;
}
