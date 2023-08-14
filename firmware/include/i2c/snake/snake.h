#ifndef INCLUDE_I2C_SNAKE_SNAKE_H_
#define INCLUDE_I2C_SNAKE_SNAKE_H_

#include "oled_geom.h"
#include "oled_text.h"
#include "buttons.h"
#include "stdlib.h"

typedef struct{
	uint8_t x;
	uint8_t y;
} snakePartsCoord;


#define FRAME_UP_LEFT_X 1
#define FRAME_UP_LEFT_Y 1

#define FRAME_BOT_RIGHT_X 124
#define FRAME_BOT_RIGHT_Y 58


#define SNAKE_SIZE_MAX 50

#define SNAKE_SIZE_BLOCK 4
#define SNAKE_SIZE_BETWEEN_PARTS 2
#define SNAKE_SIZE_PART (SNAKE_SIZE_BLOCK + SNAKE_SIZE_BETWEEN_PARTS)




void snakeInit(void);

void snakeGame(void);

#endif /* INCLUDE_I2C_SNAKE_SNAKE_H_ */
