#include "i2c_lld.h"

static I2CDriver    *i2c1 = &I2CD1;

static const I2CConfig i2c_conf = {
    .timingr = STM32_TIMINGR_PRESC(14U)  |
    STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
    STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
    .cr1 = 0,
    .cr2 = 0
};

/**
 * @brief   Starts hardware i2c module as master.
 *
 * @note	I2CD1 is used.
 */
void i2cSimpleInit(void){

	palSetLineMode(SCL_LINE, SCL_MODE | PAL_STM32_OTYPE_OPENDRAIN |
							 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);
	palSetLineMode(SDA_LINE, SDA_MODE | PAL_STM32_OTYPE_OPENDRAIN |
						 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_PULLUP);

	i2cStart(i2c1, &i2c_conf);

}

/**
 * @brief   Stops hardware i2c module as master.
 *
 * @note	I2CD1 is used.
 */
void i2cSimpleStop(void){
	i2cStop(i2c1);
}

/**
 * @brief   Writes multiple bytes of data from slave
 * @param
 *          address         7 bit address of slave device
 *          txbuf           link to a buffer array with data to write
 *          length          number of bytes to write
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
 * @brief   Reads multiple bytes of data from slave
 *
 * @param
 *          address         7 bit address of slave device
 *          rxbuf           link to a buffer array where to store read data
 *          length          number of bytes to read
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

/**
 * @brief   Reads multiple bytes of data from specific register of slave
 * @details Function writes register address data to slave and then performs
 *          repeated start action with read bit set
 * @param
 *          address         7 bit address of slave device
 *          reg_addr   		address of register to read
 *          reg_length      number of bytes to write
 *          rxbuf           link to a buffer array where to store read data
 *          rxbuf_length    number of bytes to read
 *
 * @return                  The operation status.
 * @retval  MSG_OK          if the function succeeded.
 * @retval  MSG_RESET       if one or more I2C errors occurred, the errors can
 *                          be retrieved using @p i2cGetErrors().
 * @retval  MSG_TIMEOUT     if a timeout occurred before operation end.
 */
msg_t i2cRegisterRead(uint8_t address, uint8_t *reg_addr, uint8_t reg_lenght, uint8_t *rxbuf, uint8_t rxbuf_length){
	return i2cMasterTransmitTimeout(i2c1, address, reg_addr, reg_lenght, rxbuf, rxbuf_length, 1000);
}
