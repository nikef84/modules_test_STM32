#ifndef INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_
#define INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_

#include "common.h"


//Types of fonts.
#define FONT_6x8		0
#define FONT_12x16		1


// Pixel size of the font_6x8.
#define FONT_6x8_X	6
#define FONT_6x8_Y	8

// Pixel size of the font_6x8.
#define FONT_12x16_X	12
#define FONT_12x16_Y	16


// From "space to "unknown character" chars.
#define SYMB_MAX		127
#define SYMB_MIN		32

// To remove unnecessary characters up to "space" symbol in the asci table.
#define FONT_DIFF		SYMB_MIN




/*
 * @brief	Gets the colom of the symbol.
 *
 * @note	Font6x8.
 *
 * @param_in	symb	The desired character.
 * 				colom	The number of the colom of the symbol that stores the pixels that need to be filled.
 *
 * @param_out	The colom of pixels.
 */
uint8_t font6x8GetElement(char symb, uint8_t colom);


/*
 * @brief	Gets half of the colom of the symbol.
 *
 * @note	Font12x16.
 *
 * @param_in	symb	The desired character.
 * 				colom	The number of the colom of the symbol that stores the pixels that need to be filled.
 *
 * @param_out	The colom of pixels.
 */
uint8_t font12x16GetElement(char symb, uint8_t colom);

#endif /* INCLUDE_I2C_OLED_DISPLAY_OLED_FONTS_H_ */
