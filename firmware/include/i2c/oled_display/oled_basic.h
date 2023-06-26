#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_BASIC_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_BASIC_H_

#include "common.h"
#include "i2c_lld.h"
#include "stdlib.h"

// Address of the oled-display. OLED - oled-display.
#define OLED_ADDR						0x3C

// It is needed to whrite to the registers.
#define OLED_REG_WRITE_SETT				0x80

#define OLED_DISPLAY_ON					0xAF
#define OLED_DISPLAY_OFF				0xAE

// Screen sizes.
#define OLED_LENGHT						128
#define OLED_HEIGHT						64
#define OLED_BYTES_PER_COLOM			(OLED_HEIGHT / 8)

// Buffer.
#define OLED_PIC_BUF_SIZE				OLED_LENGHT * OLED_HEIGHT / OLED_BYTES_PER_COLOM
#define OLED_BUF_SEPARATOR				8
#define OLED_SEPAR_BUF_SIZE				(OLED_PIC_BUF_SIZE / OLED_BUF_SEPARATOR) + 1

// Colors.
#define COLOR_WHITE						1
#define COLOR_BLACK						0



/*
 * @brief	Writes a register address to the oled display.
 *
 * @param_in	reg_address 	The address of the register which we want to write.
 * 							  	Must be 1 byte!
 */
void oledRegisterWriteReg(uint8_t reg_address);


/*
 * @brief	Writes one byte of the data to the oled display.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 1 bytes!
 *
 * 				data 			The information we want to write to the oled display.
 * 								Must be 1 byte!
 */
void oledRegisterWriteFour(uint8_t reg_address, uint8_t data);


/*
 * @brief	Writes two bytes of the data to the oled display.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 1 bytes!
 *
 * 				data 			The information we want to write to the oled display.
 * 								Must be 1 byte!
 *
 * 				data1 			The information we want to write to the oled display.
 * 								Must be 1 byte!
 */
void oledRegisterWriteSix(uint8_t reg_address, uint8_t data, uint8_t data1);


/*
 * @brief 	Inits I2C and sets the settings to the oled display.
 *
 * @note I2CD1 is used.
 */
void oledInit(void);


/*
 * @brief	Inverts the colors on the screen.
 *
 * @param_in	state_invert	Inverts / doesn't invert the colors.
 */
void oledInvertColor(bool state_invert);


/*
 * @brief	Turns on the screen.
 */
void oledDisplayOn(void);


/*
 * @brief Turns off the screen.
 */
void oledDisplayOff(void);


/*
 * @brief	Dispays the buffer on the led screen.
 *
 * @note	The buffer spits by OLED_BUF_SEPARATOR, because of i2cTransmit lenght.
 * 			256 - max.
 */
void oledUpdatePic(void);


/*
 * @brief	Draw the pixel on the screen.
 *
 * @note	The color depends on color_draw.
 *
 * @param_in	x	Horizontal pixel number.
 * 				y	Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 */
void oledDrawPixel(uint8_t x, uint8_t y);


/*
 * @brief	Returns the COLOR of the pixel.
 *
 * @param_in	x	Horizontal pixel number.
 * 				y	Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @param_out	color_field
 *
 * @note	COLOR_WHITE - 1
 * 			COLOR_BLACK - 0
 */
uint8_t oledGetPixel(uint8_t x, uint8_t y);


/*
 * @brief	Sets the drawing color.
 *
 * @param_in 	color	New drawing color.
 *
 * @note	COLOR_WHITE - 1
 * 			COLOR_BLACK - 0
 */
void oledSetColorDraw(uint8_t color);


/*
 * @brief	Gets the current drawing color.
 *
 * @param_out 	color_draw		New drawing color.
 *
 * @note	COLOR_WHITE - 1
 * 			COLOR_BLACK - 0
 */
uint8_t oledGetColorDraw(void);


/*
 * @brief	Clears the buffer and update the display.
 */
void oledClear(void);


#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_BASIC_H_ */
