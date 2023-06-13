#include "common.h"
#include "terminal_write.h"
#include "i2c_lld.h"



void laser_rangefinder_test(void){
    halInit();
    chSysInit();
    uint8_t data = 2;

    debugStreamInit();
    i2cDeviceInit(DEVICE_LR);
    chThdSleepMilliseconds(100);
    dbgPrintf("Start\r\n");
    msg_t msg = MSG_TIMEOUT;
    dbgPrintf("%d\r\n", msg);
    dbgPrintf("%d\r\n", i2cGetErrors(&I2CD1));
    while (true) {
        msg = i2cRegisterRead(DEVICE_LR, 0x016, &data, 1);
    	uint16_t t = 0;
//        msg_t msg = i2cMasterTransmitTimeout(&I2CD1, 0b0101001, (uint8_t *) &t, 2, &data, 1, 1000);


        chThdSleepMilliseconds(100);
		dbgPrintf("%d\t%d\r\n", data, msg);

    }
}

//static const I2CConfig i2c1conf = {
//    .timingr = STM32_TIMINGR_PRESC(14U)  |
//    STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
//    STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
//    .cr1 = 0,
//    .cr2 = 0
//};
//
//// ������� ��������� �� ������� � ����������
//static I2CDriver* i2c1 =  &I2CD1;
//
//void laser_rangefinder_test(void) {
//    halInit();
//    chSysInit();
//    // �������� ��������
//    i2cStart(i2c1, &i2c1conf);
//    // ��������� ���� B8 � B9 � ����� i2c1
//    palSetLineMode(PAL_LINE(GPIOB, 8), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
//    palSetLineMode(PAL_LINE(GPIOB, 9), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
//    // �������� ������� ��� ������ � ������ ������
//    uint8_t txbuf[1] = {0x16};
//    uint8_t rxbuf[1] = {0};
//    // ��������� � ���������� � ������� 1101010 �������� �� �������� �� ������ 0x0F (������� WHO_AM_I ��������� l3gd20h)
//
//    // ���� ���������� �������� ������������ ����������, ������ ������ ���������
//    if (rxbuf[0] == 0b11010111) palSetLine(LINE_LED1);
//    // �������� ������� ������
//    i2cflags_t flag = i2cGetErrors(i2c1);
//    // ���� �� ������ ACK ���, ������ ������ ���������
//    if (flag == I2C_ACK_FAILURE) palSetLine(LINE_LED2);
//    while (true) {
//        msg_t msg = i2cMasterTransmitTimeout(i2c1, 0b1101010, txbuf, 1, rxbuf, 1, 1000);
//
//        chThdSleepMilliseconds(1000);
//    }
//}
