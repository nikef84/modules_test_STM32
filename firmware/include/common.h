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
#define OLED_ANIMATION_CAT			4
#define OLED_BASIC					5
#define OLED_GEOM					6
#define OLED_TEXT					7
#define SNAKE						8

// Selection of program to run
#define PROGRAM_ROUTINE SNAKE

#endif /* INCLUDE_COMMON_H_ */
