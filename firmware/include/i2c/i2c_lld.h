#ifndef INCLUDE_I2C_I2C_LLD_H_
#define INCLUDE_I2C_I2C_LLD_H_

#include "common.h"

// Legs of I2C.
#define SCL_LINE 		PAL_LINE(GPIOB, 8)
#define SDA_LINE   		PAL_LINE(GPIOB, 9)

#define SCL_MODE 		PAL_MODE_ALTERNATE(4)
#define SDA_MODE   		PAL_MODE_ALTERNATE(4)


/**
 * @brief   Starts hardware i2c module as master.
 *
 * @note	I2CD1 is used.
 */
void i2cSimpleInit(void);

/**
 * @brief   Stops hardware i2c module as master.
 *
 * @note	I2CD1 is used.
 */
void i2cSimpleStop(void);

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
msg_t i2cSimpleWrite(uint8_t address, uint8_t *txbuf, uint8_t length);

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
msg_t i2cSimpleRead(uint8_t address, uint8_t *rxbuf, uint8_t length);

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
msg_t i2cRegisterRead(uint8_t address, uint8_t *reg_addr, uint8_t reg_lenght, uint8_t *rxbuf, uint8_t rxbuf_length);

#endif /* INCLUDE_I2C_I2C_LLD_H_ */
