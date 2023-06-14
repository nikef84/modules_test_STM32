#ifndef INCLUDE_I2C_I2C_LLD_H_
#define INCLUDE_I2C_I2C_LLD_H_

#include "common.h"


#define SCL_LINE 		PAL_LINE(GPIOB, 8)
#define SDA_LINE   		PAL_LINE(GPIOB, 9)

#define SCL_MODE 		PAL_MODE_ALTERNATE(4)
#define SDA_MODE   		PAL_MODE_ALTERNATE(4)

void i2cSimpleInit(void);
void i2cSimpleStop(void);
msg_t i2cSimpleWrite(uint8_t address, uint8_t *txbuf, uint8_t length);
msg_t i2cSimpleRead(uint8_t address, uint8_t *rxbuf, uint8_t length);
msg_t i2cRegisterRead(uint8_t address, uint16_t register_addr, uint8_t *rxbuf, uint8_t length);

#endif /* INCLUDE_I2C_I2C_LLD_H_ */
