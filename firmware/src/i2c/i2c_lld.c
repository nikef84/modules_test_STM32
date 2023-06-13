#include "i2c_lld.h"

static I2CDriver    *LR_Driver = &I2CD1; // LR - laser rengefinder.

static const I2CConfig i2c_conf = {
    .timingr = STM32_TIMINGR_PRESC(14U)  |
    STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
    STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
    .cr1 = 0,
    .cr2 = 0
};

/**
 * @brief   Start hardware i2c module as master
 */
void i2cDeviceInit(uint8_t device){
	switch (device){
	case DEVICE_LR:
		palSetLineMode(LR_SCL_LINE, LR_SCL_MODE | PAL_STM32_OTYPE_OPENDRAIN |
								 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
		palSetLineMode(LR_SDA_LINE, LR_SDA_MODE | PAL_STM32_OTYPE_OPENDRAIN |
							 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);

		i2cStart(LR_Driver, &i2c_conf);
		break;
	default:
		break;
	}
}

void i2cDeviceStop(uint8_t device){
	switch (device){
	case DEVICE_LR:
		i2cStop(LR_Driver);
		break;
	default:
		break;
	}
}

/**
 * @brief   Write multiple bytes of data from slave
 * @param
 *          address         7 bit address of slave device
 *          txbuf           link to a buffer array with data to write
 *          length          number of bytes to write
 *          timeout         timeout value [ms]
 *
 * @return                  The operation status.
 * @retval  MSG_OK          if the function succeeded.
 * @retval  MSG_RESET       if one or more I2C errors occurred, the errors can
 *                          be retrieved using @p i2cGetErrors().
 * @retval  MSG_TIMEOUT     if a timeout occurred before operation end.
 */
msg_t i2cSimpleWrite(uint8_t device, uint8_t *txbuf, uint8_t length){
	msg_t msg;
	switch (device){
	case DEVICE_LR:
		msg = i2cMasterTransmitTimeout(LR_Driver, LR_ADDRESS, txbuf, length, NULL, 0, 1000);
		break;
	default:
		break;
	}
    return msg;
}


/**
 * @brief   Read multiple bytes of data from slave
 *
 * @param
 *          address         7 bit address of slave device
 *          rxbuf           link to a buffer array where to store read data
 *          length          number of bytes to read
 *          timeout         timeout value [ms]
 *
 * @return                  The operation status.
 * @retval  MSG_OK          if the function succeeded.
 * @retval  MSG_RESET       if one or more I2C errors occurred, the errors can
 *                          be retrieved using @p i2cGetErrors().
 * @retval  MSG_TIMEOUT     if a timeout occurred before operation end.
 */
msg_t i2cSimpleRead(uint8_t device, uint8_t *rxbuf, uint8_t length){
	msg_t msg;
	switch (device){
	case DEVICE_LR:
		msg = i2cMasterReceiveTimeout(LR_Driver, LR_ADDRESS, rxbuf, length, 1000);
		break;
	default:
		break;
	}
    return msg;
}
#include "terminal_write.h"
uint16_t register_address[1] = {0};
/**
 * @brief   Read multiple bytes of data from specific register of slave
 * @details Function writes register address data to slave and then performs
 *          repeated start action with read bit set
 * @param
 *          address         7 bit address of slave device
 *          register_addr   address of register to read
 *          rxbuf           link to a buffer array where to store read data
 *          length          number of bytes to read
 *          timeout         timeout value [ms]
 *
 * @return                  The operation status.
 * @retval  MSG_OK          if the function succeeded.
 * @retval  MSG_RESET       if one or more I2C errors occurred, the errors can
 *                          be retrieved using @p i2cGetErrors().
 * @retval  MSG_TIMEOUT     if a timeout occurred before operation end.
 */
msg_t i2cRegisterRead(uint8_t device, uint16_t register_addr, uint8_t *rxbuf, uint8_t length){
	msg_t msg;
    register_address[0] = register_addr;
    dbgPrintf("add = %d\r\n", register_address[0]);
	switch (device){
	case DEVICE_LR:
		dbgPrintf("%d\r\n", *rxbuf);
		msg = i2cMasterTransmitTimeout(LR_Driver, LR_ADDRESS, (uint8_t *)register_address, 2, rxbuf, length, 1000);
		dbgPrintf("%d\r\n", *rxbuf);
		break;
	default:
		break;
	}
    return msg;
}
