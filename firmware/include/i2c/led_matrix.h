#ifndef INCLUDE_I2C_LED_MATRIX_H_
#define INCLUDE_I2C_LED_MATRIX_H_

#include "common.h"
#include "i2c_lld.h"

#define LM_ADDRESS	0b1100000

void lmInit(void);
void lmRegisterWrite(uint8_t reg_address, uint8_t data);
#endif /* INCLUDE_I2C_LED_MATRIX_H_ */
