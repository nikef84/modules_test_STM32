#include "oled_display.h"
#include "terminal_write.h"

uint8_t buf[1024] = {0};

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
	oledClear();
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
		buf[i] |= 1 << (y % 8);
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
            	//dbgPrintf("x = %d\t y = %d\r\n", (y - y1) * dx / dy + x1, y);
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

void oledDrawCircle(uint8_t X1, uint8_t Y1, uint8_t R){
	uint8_t x, y;
	int16_t delta, error;
	while (R != 0){
		x = 0;
		y = R;
		delta = 1 - 2 * R;
		error = 0;
		while (y >= x){
			oledDrawPixel(X1 + x, Y1 + y);
			oledDrawPixel(X1 + x, Y1 - y);
			oledDrawPixel(X1 - x, Y1 + y);
			oledDrawPixel(X1 - x, Y1 - y);
			oledDrawPixel(X1 + y, Y1 + x);
			oledDrawPixel(X1 + y, Y1 - x);
			oledDrawPixel(X1 - y, Y1 + x);
			oledDrawPixel(X1 - y, Y1 - x);
			error = 2 * (delta + y) - 1;
			if ((delta < 0) && (error <= 0)){
				delta += 2 * ++x + 1;
				continue;
			}
			if ((delta > 0) && (error > 0)){
				delta -= 2 * --y + 1;
				continue;
			}
			delta += 2 * (++x - --y);
		}
		R--;
	}

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
