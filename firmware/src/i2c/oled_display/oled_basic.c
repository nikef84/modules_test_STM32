#include "oled_basic.h"
#include "terminal_write.h"

// The buffer of the image that will be displayed on the screen.
uint8_t buf[OLED_PIC_BUF_SIZE] = {0};

static uint8_t color_field = COLOR_BLACK; // The color of the screen field.
static uint8_t color_draw = COLOR_WHITE; // The color that is drawn on the screen.

/*
 * @brief	Writes a register address to the oled display.
 *
 * @param_in	reg_address 	The address of the register which we want to write.
 * 							  	Must be 1 byte!
 */
void oledRegisterWriteReg(uint8_t reg_address){
	uint8_t txbuf[2] = {OLED_REG_WRITE_SETT, reg_address};
	i2cSimpleWrite(OLED_ADDR, txbuf, 2);
//	chThdSleepMilliseconds(1);
}

/*
 * @brief	Writes one byte of the data to the oled display.
 *
 * @param_in	reg_address 	The address of the register to which we want to write information.
 * 							  	Must be 1 bytes!
 *
 * 				data 			The information we want to write to the oled display.
 * 								Must be 1 byte!
 */
void oledRegisterWriteFour(uint8_t reg_address, uint8_t data){
	uint8_t txbuf[4] = {OLED_REG_WRITE_SETT, reg_address, OLED_REG_WRITE_SETT, data};
	i2cSimpleWrite(OLED_ADDR, txbuf, 4);
//	chThdSleepMilliseconds(1);
}

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
void oledRegisterWriteSix(uint8_t reg_address, uint8_t data, uint8_t data1){
	uint8_t txbuf[6] = {OLED_REG_WRITE_SETT, reg_address, OLED_REG_WRITE_SETT, data,
						OLED_REG_WRITE_SETT, data1};
	i2cSimpleWrite(OLED_ADDR, txbuf, 6);
	//chThdSleepMilliseconds(1);
}

/*
 * @brief 	Inits I2C and sets the settings to the oled display.
 *
 * @note I2CD1 is used.
 */
void oledInit(void){
	i2cSimpleInit(); // Starts I2C.

	// Sets settings to the oled display.
	oledDisplayOff();
	oledRegisterWriteFour(0xD5, 0x80);
	oledRegisterWriteFour(0xA8, 0x3F);
	oledRegisterWriteFour(0xD3, 0x00);
	oledRegisterWriteFour(0x80, 0x40 | 0);
	oledRegisterWriteFour(0x8D, 0x14);
	oledRegisterWriteFour(0x20, 0x01);
	oledRegisterWriteReg(0xA1);
	oledRegisterWriteReg(0xC8);
	oledRegisterWriteFour(0xDA, 0x12);
	oledRegisterWriteFour(0x81, 0xFF);
	oledRegisterWriteFour(0xD9, 0xF1);
	oledRegisterWriteFour(0xDB, 0x40);
	oledRegisterWriteReg(0xA4);
	oledRegisterWriteReg(0xA6);
	oledDisplayOn();

	oledInvertColor(false); // Doesn't invert the colors on the screen.

	oledClear(); // Clears the screen.
}

/*
 * @brief	Inverts the colors on the screen.
 *
 * @param_in	state_invert	Inverts / doesn't invert the colors.
 */
void oledInvertColor(bool state_invert){
	if (state_invert == true){ // Inverts.
		color_field = COLOR_WHITE;
		color_draw = COLOR_BLACK;
		oledRegisterWriteReg(0xA7);
	}
	else{ // Doesn't invert.
		color_field = COLOR_BLACK;
		color_draw = COLOR_WHITE;
		oledRegisterWriteReg(0xA6);
	}
}

/*
 * @brief	Turns on the screen.
 */
void oledDisplayOn(void){
	oledRegisterWriteReg(OLED_DISPLAY_ON);
}

/*
 * @brief Turns off the screen.
 */
void oledDisplayOff(void){
	oledRegisterWriteReg(OLED_DISPLAY_OFF);
}

/*
 * @brief	Dispays the buffer on the led screen.
 *
 * @note	The buffer spits by OLED_BUF_SEPARATOR, because of i2cTransmit lenght.
 * 			256 - max.
 */
void oledUpdatePic(void){
	uint8_t colom [OLED_SEPAR_BUF_SIZE] = {0x00}; // Temp buf.
	for (uint8_t i = 0; i != 8; i++){ // Splits the buffer.
		colom[0] = 0x40;
		for (uint8_t j = 0; j != (uint8_t)(OLED_SEPAR_BUF_SIZE - 1); j++){
			colom[j + 1] = buf[i*(OLED_SEPAR_BUF_SIZE - 1) + j];
		}
		oledRegisterWriteSix(0x22, 0, 7);
		oledRegisterWriteSix(0x21, i*((OLED_SEPAR_BUF_SIZE - 1) / OLED_BYTES_PER_COLOM),
							 (i+1)*((OLED_SEPAR_BUF_SIZE - 1) / OLED_BYTES_PER_COLOM) - 1);
		i2cSimpleWrite(OLED_ADDR, colom, (uint8_t)OLED_SEPAR_BUF_SIZE); // Display the temp buf.
	}
}

// To shift down the img.
static uint8_t mask[] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};


/*
 * @brief	Shifts down the img.
 *
 * @note	 Shifts the img from 1 to 7 bits.
 *
 * @param_in	buf			An array which will be shifted.
 * 				buf_size	Size of buf in bytes.
 * 				step		The number of bits to be shifted.
 *
 * @notapi
 */
void shift_down(uint8_t *buf, uint8_t step){
	uint8_t last_elem = 8 - 1;
	buf[last_elem] = (buf[last_elem] << step) & mask[7];
	for (uint8_t i = 0; i < OLED_BYTES_PER_COLOM - 1; i++){
		buf[last_elem - i] |= (buf[last_elem - i - 1] >> (BITS_IN_BYTE - step)) & mask[step];
		buf[last_elem - i - 1] = (buf[last_elem - i - 1] << step) & mask[7];
	}
}


/*
 * @brief	Draw the img to the screen.
 *
 * @param_in	img		An array in which a set of pixels is stored that needs to be lit.
 * 						The values should be stored line by line, from left to right.
 * 						MUST BE: img[0] = horizontal lenght of the img in bits.
 * 								 img[1] = vertical lenght og the img in bits.
 *
 * 				x1		Horizontal coordinate of the upper-left corner of the img.
 * 				y1 		Vertical coordinate of the upper-left corner of the img.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 */
void oledDrawImg(uint8_t *img, uint8_t x, uint8_t y){
	uint8_t bytes = img[1] / BITS_IN_BYTE;
	uint8_t colom[OLED_BYTES_PER_COLOM] = {0x00};
	uint16_t pos;
	for (uint8_t col = 0; col < img[0]; col++){
		if (col + x >= OLED_LENGHT) break; // X is out of screen range.
		for (uint8_t i = 0; i < OLED_BYTES_PER_COLOM; i++) colom[i] = 0;

		pos = ((x + col) * OLED_BYTES_PER_COLOM) + (y / OLED_BYTES_PER_COLOM);
		for (uint8_t str = 0; str < bytes; str++){
			if (pos + str == ((x + col + 1) * OLED_BYTES_PER_COLOM))break; // y is out of screen range.
			colom[(pos + str) % 8] =  img[str * img[0] + col + 2];
		}

		if (y % 8 != 0) shift_down(colom, y % 8); // Shifts the colom down.
		pos = ((x + col) * OLED_BYTES_PER_COLOM);
		for (uint8_t str = 0; str < OLED_BYTES_PER_COLOM; str++){
			buf[pos + str] |= colom[str];
		}
	}
}

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
void oledDrawPixel(uint8_t x, uint8_t y){
	if (x < OLED_LENGHT && y < OLED_HEIGHT){
		uint16_t i = (x * OLED_BYTES_PER_COLOM) + (y / OLED_BYTES_PER_COLOM);
		if (color_field != color_draw) buf[i] |= 1 << (y % OLED_BYTES_PER_COLOM);
		else {
			buf[i] &= ~(1 << (y % OLED_BYTES_PER_COLOM));
		}
	}
}

/*
 * @brief	Returns the COLOR of the pixel.
 *
 * @param_in	x	Horizontal pixel number.
 * 				y	Vertical pixel number.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.*
 *
 * @param_out	color_field
 *
 * @note	COLOR_WHITE - 1
 * 			COLOR_BLACK - 0
 */
uint8_t oledGetPixel(uint8_t x, uint8_t y){
	uint8_t temp;
	if (x < OLED_LENGHT && y < OLED_HEIGHT){
		uint16_t i = (x * OLED_BYTES_PER_COLOM) + (y / OLED_BYTES_PER_COLOM);
		temp = buf[i] & 1 << (y % OLED_BYTES_PER_COLOM);
		if (color_field == COLOR_BLACK){ // The screen is iverted or not.
			if (temp != 0) return COLOR_WHITE;
			else return COLOR_BLACK;
		}
		else{
			if (temp != 0) return COLOR_BLACK;
			else return COLOR_WHITE;
		}
	}
	else return color_field;
}

/*
 * @brief	Sets the drawing color.
 *
 * @param_in 	color	New drawing color.
 *
 * @note	COLOR_WHITE - 1
 * 			COLOR_BLACK - 0
 */
void oledSetColorDraw(uint8_t color){
	color_draw = color;
}

/*
 * @brief	Gets the current drawing color.
 *
 * @param_out 	color_draw		New drawing color.
 *
 * @note	COLOR_WHITE - 1
 * 			COLOR_BLACK - 0
 */
uint8_t oledGetColorDraw(void){
	return color_draw;
}

/*
 * @brief	Clears the buffer and update the display.
 */
void oledClear(void){
	oledClearBuf();
	oledUpdatePic();
}

/*
 * @brief	Clears the buffer.
 */
void oledClearBuf(void){
	for (uint16_t i = 0; i != OLED_PIC_BUF_SIZE; i++) buf[i] = 0;
}
