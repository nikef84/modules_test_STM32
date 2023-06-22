// Header file to select program to run

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <hal.h>
#include <ch.h>
#include <chprintf.h>
#include <tests.h>

// List of all possible programs
#define MAIN_ROUTINE              	0
#define I2C				         	1
#define LASER_RANGEFINDER         	2
#define LED_MATRIX		         	3
#define GYRO		         		4


// Selection of program to run
#define PROGRAM_ROUTINE LED_MATRIX

#endif /* INCLUDE_COMMON_H_ */
