#include "oled_display.h"
#include "terminal_write.h"

uint8_t buf[1024] = {0};

static uint8_t color_field = COLOR_BLACK;
static uint8_t color_draw = COLOR_WHITE;

void oledInit(void){
	i2cSimpleInit();
	oledRegisterWriteTwo(0xAE);
	oledRegisterWriteFour(0xD5, 0x80);
	oledRegisterWriteFour(0xA8, 0x3F);
	oledRegisterWriteFour(0xD3, 0x00);
	oledRegisterWriteFour(0x80, 0x40 | 0);
	oledRegisterWriteFour(0x8D, 0x14);
	oledRegisterWriteFour(0x20, 0x01);
	oledRegisterWriteTwo(0xA1);
	oledRegisterWriteTwo(0xC8);
	oledRegisterWriteFour(0xDA, 0x12);
	oledRegisterWriteFour(0x81, 0xFF);
	oledRegisterWriteFour(0xD9, 0xF1);
	oledRegisterWriteFour(0xDB, 0x40);
	oledRegisterWriteTwo(0xA4);
	oledRegisterWriteTwo(0xA6);
	oledRegisterWriteTwo(0xAF);

	oledInvertColor(false);

	oledClear();
}

void oledInvertColor(bool state_invert){
	if (state_invert == true){
		color_field = COLOR_WHITE;
		color_draw = COLOR_BLACK;
		oledRegisterWriteTwo(0xA7);
	}
	else{
		color_field = COLOR_BLACK;
		color_draw = COLOR_WHITE;
		oledRegisterWriteTwo(0xA6);
	}
}

void oledUpdatePic(void){
	uint8_t colom [129] = {0x00};
	for (uint8_t i = 0; i != 8; i++){
		colom[0] = 0x40;
		for (uint8_t j = 0; j != 128; j++){
			colom[j + 1] = buf[i*128 + j];
		}
		oledRegisterWriteSix(0x22, 0, 7);
		oledRegisterWriteSix(0x21, i*16, (i+1)*16 - 1);
		i2cSimpleWrite(OLED_ADDR, colom, 129);
	}
}

void oledDrawPixel(uint8_t x, uint8_t y){
	if (x < 128 && y < 64){
		uint16_t i = (x * 8) + (y / 8);
		if (color_field != color_draw) buf[i] |= 1 << (y % 8);
		else {
			buf[i] &= ~(1 << (y % 8));
		}
	}
}

void oledDrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    int8_t dx = x2 - x1;
    int8_t dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        if (x1 < x2) {
            for (int16_t x = x1; x <= x2; x++) {
            	oledDrawPixel(x, (uint8_t)((x - x1) * dy / dx + y1));

            }
        } else {
            for (int16_t x = x1; x >= x2; x--) {
            	oledDrawPixel(x, (uint8_t)((x - x1) * dy / dx + y1));
            }
        }
    } else {
        if (y1 < y2) {
            for (int16_t y = y1; y <= y2; y++) {
            	oledDrawPixel((uint8_t)((y - y1) * dx / dy + x1), y);
            }
        } else {
            for (int16_t y = y1; y >= y2; y--) {
            	oledDrawPixel((uint8_t)((y - y1) * dx / dy + x1), y);
            }
        }
    }
}

void oled_change_fill_param(uint8_t *x1, uint8_t *x2){
	uint8_t temp;
	if (*x1 < *x2) {
		*x1 = *x1 + 1;
		*x2 = *x2 - 1;
	}
	else {
		temp = *x1;
		*x1 = *x2 + 1;
		*x2 = temp - 1;
	}
}

uint8_t oledGetColorDraw(void){
	return color_draw;
}

void oledDrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill){

	oledDrawLine(x1, y1, x1, y2);
	oledDrawLine(x2, y1, x2, y2);
	oledDrawLine(x1, y1, x2, y1);
	oledDrawLine(x1, y2, x2, y2);

	if (fill == true && (x1 != x2 && y1 != y2)){

		oled_change_fill_param(&x1, &x2);
		oled_change_fill_param(&y1, &y2);
		while (y1 <= y2){
			oledDrawLine(x1, y1, x2, y1);
			y1++;
		}
	}
}

void oledDrawCircle(uint8_t x, uint8_t y, uint8_t R){
	uint8_t x_temp, y_temp;
	int16_t delta, error;
	x_temp = 0;
	y_temp = R;
	delta = 1 - 2 * R;
	error = 0;
	while (y_temp >= x_temp){
		oledDrawPixel(x + x_temp, y + y_temp);
		oledDrawPixel(x + x_temp, y - y_temp);
		oledDrawPixel(x - x_temp, y + y_temp);
		oledDrawPixel(x - x_temp, y - y_temp);
		oledDrawPixel(x + y_temp, y + x_temp);
		oledDrawPixel(x + y_temp, y - x_temp);
		oledDrawPixel(x - y_temp, y + x_temp);
		oledDrawPixel(x - y_temp, y - x_temp);
		error = 2 * (delta + y_temp) - 1;
		if ((delta < 0) && (error <= 0)){
			delta += 2 * ++x_temp + 1;
			continue;
		}
		if ((delta > 0) && (error > 0)){
			delta -= 2 * --y_temp + 1;
			continue;
		}
		delta += 2 * (++x_temp - --y_temp);
	}
}

void oledChangeColorDraw(uint8_t color){
	color_draw = color;
}

uint8_t oledGetPixel(uint8_t x, uint8_t y){
	uint8_t temp;
	if (x < 128 && y < 64){
		uint16_t i = (x * 8) + (y / 8);
		temp = buf[i] & 1 << (y % 8);
		if (color_field == COLOR_BLACK){
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




void oledClear(void){
	for (uint16_t i = 0; i != 1024; i++) buf[i] = 0;
	oledUpdatePic();
}

void oledRegisterWriteTwo(uint8_t reg_address){
	uint8_t txbuf[2] = {0x80, reg_address};
	i2cSimpleWrite(OLED_ADDR, txbuf, 2);
	chThdSleepMilliseconds(1);
}

void oledRegisterWriteFour(uint8_t reg_address, uint8_t data){
	uint8_t txbuf[4] = {0x80, reg_address, 0x80, data};
	i2cSimpleWrite(OLED_ADDR, txbuf, 4);
	chThdSleepMilliseconds(1);
}

void oledRegisterWriteSix(uint8_t reg_address, uint8_t data, uint8_t data1){
	uint8_t txbuf[6] = {0x80, reg_address, 0x80, data, 0x80, data1};
	i2cSimpleWrite(OLED_ADDR, txbuf, 6);
	chThdSleepMilliseconds(1);
}
