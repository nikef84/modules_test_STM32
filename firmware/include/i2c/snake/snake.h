#ifndef INCLUDE_I2C_SNAKE_SNAKE_H_
#define INCLUDE_I2C_SNAKE_SNAKE_H_

#include "oled_geom.h"
#include "oled_text.h"
#include "buttons.h"
#include "stdlib.h"

// Template for coordinates.
typedef struct{
	uint8_t x;
	uint8_t y;
} coords_t;

// Game status.
typedef  enum
{
	READY = 0, // Inital and "in game" value.
	LOSE  = 1, // Game over.
	WIN   = 2 // You win.
}gamestatus_t;


// Frame cornenrs.
#define FRAME_UP_LEFT_X 			1
#define FRAME_UP_LEFT_Y 			1

#define FRAME_BOT_RIGHT_X 			124
#define FRAME_BOT_RIGHT_Y 			58

// Sizes of the snake parts.
#define SNAKE_SIZE_BLOCK 			4
#define SNAKE_SIZE_BETWEEN_PARTS 	2
#define SNAKE_SIZE_PART 			(SNAKE_SIZE_BLOCK + SNAKE_SIZE_BETWEEN_PARTS)

// The maximum number of snake parts. And a finish score too.
#define SNAKE_SIZE_MAX 				20
// The initial lenght of the snake
#define SNAKE_SIZE_INIT 			3 // 15 max!


// Speed of the snake.
#define SNAKE_GAME_SPEED			5 // Frames in 1 second. Max is 10!
#define SNAKE_GAME_PERIOD			(1000 / SNAKE_GAME_SPEED) // In ms.

/*
 * @brief	Inits the snake game.
 *
 * @note	Inits buttons to play.
 *
 * @note	Inits the oled display.
 */
void snakeInit(void);

/*
 * @brief	Makes one move of the snake and checks for the result (Main game);
 *
 * @note	Use in a loop!
 */
void snakeGame(void);

#endif /* INCLUDE_I2C_SNAKE_SNAKE_H_ */
