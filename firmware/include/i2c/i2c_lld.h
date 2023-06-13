#ifndef INCLUDE_I2C_I2C_LLD_H_
#define INCLUDE_I2C_I2C_LLD_H_

#include "common.h"


#define DEVICE_LR		0


#define LR_ADDRESS		0b0101001

#define LR_SCL_LINE 		PAL_LINE(GPIOB, 8)
#define LR_SDA_LINE   		PAL_LINE(GPIOB, 9)

#define LR_SCL_MODE 		PAL_MODE_ALTERNATE(4)
#define LR_SDA_MODE   		PAL_MODE_ALTERNATE(4)

void i2cDeviceInit(uint8_t device);
void i2cDeviceStop(uint8_t device);
msg_t i2cSimpleWrite(uint8_t device, uint8_t *txbuf, uint8_t length);
msg_t i2cSimpleRead(uint8_t device, uint8_t *rxbuf, uint8_t length);
msg_t i2cRegisterRead(uint8_t device, uint16_t register_addr, uint8_t *rxbuf, uint8_t length);

#endif /* INCLUDE_I2C_I2C_LLD_H_ */
