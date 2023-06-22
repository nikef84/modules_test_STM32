#ifndef INCLUDE_I2C_LED_MATRIX_H_
#define INCLUDE_I2C_LED_MATRIX_H_

#include "common.h"
#include "i2c_lld.h"

// Address of the led matrix. LM - led matrix.
#define LM_ADDRESS				0b1100000

// Registers.
#define REG_BRIGHTNESS			0x0D
#define REG_SETTINGS			0x00

#define REG_LINE_1				0x01
#define REG_LINE_2				0x02
#define REG_LINE_3				0x03
#define REG_LINE_4				0x04
#define REG_LINE_5				0x05
#define REG_LINE_6				0x06
#define REG_LINE_7				0x07
#define REG_LINE_8				0x08

#define REG_CONFIRM_PIC			0x0C

// Registers possible value.
#define INIT_SETTINGS			0x00

// Must be from 0x08 to 0x0C, because of the current.
#define BRIGHTNESS_10			0x0C
#define BRIGHTNESS_8			0x0B
#define BRIGHTNESS_6			0x0A
#define BRIGHTNESS_4			0x09
#define BRIGHTNESS_2			0x08



/*
 * @brief 	Inits I2C and sets the settings to the led matrix.
 *
 * @note I2CD1 is used.
 */
void lmInit(void);

/*
 * @brief	Writes the data to the led matrix.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 1 byte!
 *
 * 				data 			The information we want to write to the selected register.
 * 								Must be 1 byte!
 */
void lmRegisterWrite(uint8_t reg_address, uint8_t data);

/*
 * @brief	Displays the picture on the led matrix.
 *
 * @param_in	picture		1D array in which each elemet is a string of led matrix.
 * 							Must consist of 8 elements.
 */
void lmSetPicture(uint8_t *picture);

/*
 * @brief	Clears the led matrix.
 */
void lmClearPic(void);

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
void lmPicHeart(void);

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
void lmPicSkull(void);

/*
 * @brief	Change the brightness of the led matrix.
 *
 * @param_in	brightness	The new value of brightness.
 * 							Must be from 0x08 to 0x0C, because of the current.
 */
void lmChangeBrightness(uint8_t brightness);

/*
 * @brief	Change the brightness of the led matrix gradually.
 *
 * @note 	Use it in a loop.
 */
void lmGradientBrightness(void);


#endif /* INCLUDE_I2C_LED_MATRIX_H_ */
