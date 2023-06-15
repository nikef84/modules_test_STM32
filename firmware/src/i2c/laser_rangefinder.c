#include "laser_rangefinder.h"
#include "terminal_write.h"

msg_t msg_error = MSG_OK;

void set_init_setting(void){

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

	lrRegisterWrite(0x0011, 0x10);
	lrRegisterWrite(0x010a, 0x30);
	lrRegisterWrite(0x003f, 0x46);
	lrRegisterWrite(0x0031, 0xFF);
	lrRegisterWrite(0x0040, 0x63);
	lrRegisterWrite(0x002e, 0x01);

}


void lrInit(void){
	i2cSimpleInit();
	uint8_t txbuf[3];
	txbuf[0] = 0x00;
	txbuf[1] = 0x16;
	txbuf[2] = 0x1;
	i2cSimpleWrite(LR_ADDRESS, txbuf, 3);
	chThdSleepMilliseconds(10);
	uint8_t mode = lrRegisterRead(REG_SET_SETTINGS);

	if (mode == MODE_START_SET_SETTINGS){
		dbgPrintf("ok\r\n");
		set_init_setting();
		lrRegisterWrite(REG_SET_SETTINGS, MODE_STOP_SET_SETTINGS);
	}
	if (LR_MODE == CONTINUOUS_MODE)lrRegisterWrite(0x018, 0x03);

}

void lrRegisterWrite(uint16_t reg_address, uint8_t data){
	uint8_t res;
	do {
		res = lrRegisterRead(0x004d);
		//dbgPrintf("%d\r\n", res);
	} while((res & 0x01) != 1);
	uint8_t txbuf[3];
	txbuf[0] = (reg_address >> 8) & 0xFF;
	txbuf[1] = reg_address & 0xFF;
	txbuf[2] = data & 0xFF;

	msg_error = i2cSimpleWrite(LR_ADDRESS, txbuf, 3);
	chThdSleepMilliseconds(10);
}

uint8_t lrRegisterRead(uint16_t reg_address){
	uint8_t txbuf[2];
	uint8_t data = 0;
	txbuf[0] = (reg_address >> 8) & 0xFF;
	txbuf[1] = reg_address & 0xFF;
	msg_error = i2cRegisterRead(LR_ADDRESS, txbuf, 2, &data, 1);
	chThdSleepMilliseconds(10);
	return data;
}


//
//void lr_poll(void){
//	char status;
//	char range_status;
//
//	// check the status
//	status = lrRegisterRead(0x04f);
//	range_status = status & 0x07;
//
//	// wait for new measurement ready status
//	while (range_status != 0x04) {
//		status = lrRegisterRead(0x04f);
//		range_status = status & 0x07;
//		dbgPrintf("%d\r\n", status);
//	}
//}

void lr_clear_interrupts(void) {
	lrRegisterWrite(0x015,0x07);
}

uint8_t lrReadResult(void){
	//lr_poll();
	if (LR_MODE == ONE_SHOT_MODE)lrRegisterWrite(0x0018, 0x01);
	uint8_t res = lrRegisterRead(0x062);
	dbgPrintf("inter = %d\r\n", lrRegisterRead(0x015));
	lr_clear_interrupts();
	dbgPrintf("inter = %d\r\n", lrRegisterRead(0x015));
	return res;
}
