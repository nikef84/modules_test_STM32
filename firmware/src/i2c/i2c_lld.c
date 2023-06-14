#include "i2c_lld.h"

static I2CDriver    *i2c1 = &I2CD1; // LR - laser rengefinder.

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
void i2cSimpleInit(void){

	palSetLineMode(SCL_LINE, SCL_MODE | PAL_STM32_OTYPE_OPENDRAIN |
							 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
	palSetLineMode(SDA_LINE, SDA_MODE | PAL_STM32_OTYPE_OPENDRAIN |
						 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);

	i2cStart(i2c1, &i2c_conf);

}

void i2cSimpleStop(void){
	i2cStop(i2c1);
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
msg_t i2cSimpleWrite(uint8_t address, uint8_t *txbuf, uint8_t length){
	return i2cMasterTransmitTimeout(i2c1, address, txbuf, length, NULL, 0, 1000);
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
msg_t i2cSimpleRead(uint8_t address, uint8_t *rxbuf, uint8_t length){
	return i2cMasterReceiveTimeout(i2c1, address, rxbuf, length, 1000);
}

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
msg_t i2cRegisterRead(uint8_t address, uint16_t register_addr, uint8_t *rxbuf, uint8_t length){
    register_address[0] = register_addr;
	return i2cMasterTransmitTimeout(i2c1, address, (uint8_t *)register_address, 2, rxbuf, length, 1000);
}
