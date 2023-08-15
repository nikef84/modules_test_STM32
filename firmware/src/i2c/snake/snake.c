#include "snake.h"
#include "terminal_write.h"


// Coordinates of all parts of the snake.
static snakePartsCoord snakeCoords[SNAKE_SIZE_MAX] = {
	{.x = 0, .y = 0}
};

// Apple coordinates.
static snakePartsCoord appleCoords = {
	.x = 0, .y = 0
};

// Direction of the snake.
static buttons_t snakeDiriction = RIGHT;

// The current length of the snake.
static uint8_t snakeCurrentSize = 0;

// Game status (READY, LOSE, WIN).
static gamestatus_t gameFlag = READY;

/*
 * @brief	Draw one part of the snake to the screen.
 *
 * @param_in	x	Horizontal coordinate of the top left corner of the part.
 * 				y 	Vertical coordinate of the top left corner of the part.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @notapi
 */
void snake_draw_part(uint8_t x, uint8_t y){
	oledDrawRect(x, y, x + SNAKE_SIZE_BLOCK - 1, y + SNAKE_SIZE_BLOCK - 1, true);
}

/*
 * @brief	Draw an apple to the screen.
 *
 * @param_in	x	Horizontal coordinate of the top left corner of the apple.
 * 				y 	Vertical coordinate of the top left corner of the apple.
 *
 * @note	(x, y) = (0, 0) - Upper left coner.
 *
 * @notapi
 */
void apple_draw(uint8_t x, uint8_t y){
	oledDrawLineCoord(x + 1, y, x + 2, y);
	oledDrawLineCoord(x, y + 1, x + 3, y + 1);
	oledDrawLineCoord(x, y + 2, x + 3, y + 2);
	oledDrawLineCoord(x + 1, y + 3, x + 2, y + 3);
}

/*
 * @brief	Spawn and draw an apple in a random place.
 *
 * @notapi
 */
void apple_spawn(void){
	uint8_t x, y;
	bool flag = false;
	while(!flag){ // Finds a place where an apple can be.
		y = rand() % 9; // Random number from 0 to 8.
		x = rand() % 20; // Random number from 0 to 20.

		// Count coords.
		x = x * SNAKE_SIZE_PART + 4;
		y = y * SNAKE_SIZE_PART + 4;

		// Checking that there is no part of the snake in this place.
		for(uint8_t i = 0; i < snakeCurrentSize; i++){
			if(snakeCoords[i].x == x && snakeCoords[i].y == y){
				flag = false;
				break;
			}
			flag = true;
		}
	}
	appleCoords.x = x;
	appleCoords.y = y;

	apple_draw(appleCoords.x, appleCoords.y); //  Draw an apple.
}

/*
 * @brief
 */
void snake_start(void){
	oledClearBuf();

	gameFlag = 0;
	snakeDiriction = RIGHT;

	oledDrawRect(FRAME_UP_LEFT_X, FRAME_UP_LEFT_Y, FRAME_BOT_RIGHT_X, FRAME_BOT_RIGHT_Y, false);
	oledDrawRect(FRAME_UP_LEFT_X - 1, FRAME_UP_LEFT_Y - 1, FRAME_BOT_RIGHT_X + 1, FRAME_BOT_RIGHT_Y + 1, false);

	for (uint8_t i = 0; i < SNAKE_SIZE_MAX; i++){
		snakeCoords[i].x = 0;
		snakeCoords[i].y = 0;
	}

	snakeCurrentSize = 3;
	for (uint8_t i = 0; i < snakeCurrentSize; i++){
		snakeCoords[i].x = 4 + i * SNAKE_SIZE_PART;
		snakeCoords[i].y = 28;
		snake_draw_part(snakeCoords[i].x, snakeCoords[i].y);
	}

	oledUpdatePic();
	while (buttonsGetFlagNewVal() == false)chThdSleepMilliseconds(5);
	srand((uint32_t) chVTGetSystemTime());
	apple_spawn();
	oledUpdatePic();
}

void snakeInit(void){
	oledInit();

	buttonsInit();
	chThdSleepMilliseconds(5);
	snake_start();
}

void snake_clear_last_part(void){
	oledSetColorDraw(COLOR_BLACK);
	oledDrawRect(snakeCoords[0].x, snakeCoords[0].y,
				 snakeCoords[0].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[0].y + SNAKE_SIZE_BLOCK - 1, true);
	oledSetColorDraw(COLOR_WHITE);
}


void snake_move(void){
	snake_clear_last_part();
	int8_t x_step = 0;
	int8_t y_step = 0;
	switch (snakeDiriction){
	case LEFT:
		x_step = -SNAKE_SIZE_PART;
		break;
	case RIGHT:
		x_step = SNAKE_SIZE_PART;
		break;
	case TOP:
		y_step = -SNAKE_SIZE_PART;
		break;
	case BOTTOM:
		y_step = SNAKE_SIZE_PART;
		break;
	default:
		break;
	}

	for (uint8_t i = 0; i < snakeCurrentSize - 1; i++){
		snakeCoords[i].x = snakeCoords[i + 1].x;
		snakeCoords[i].y = snakeCoords[i + 1].y;
	}
	snakeCoords[snakeCurrentSize - 1].x = snakeCoords[snakeCurrentSize - 2].x + x_step;
	snakeCoords[snakeCurrentSize - 1].y = snakeCoords[snakeCurrentSize - 2].y + y_step;

	oledDrawRect(snakeCoords[snakeCurrentSize - 1].x, snakeCoords[snakeCurrentSize - 1].y,
				 snakeCoords[snakeCurrentSize - 1].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[snakeCurrentSize - 1].y + SNAKE_SIZE_BLOCK - 1, true);

}

uint8_t crash_check(void){
	if (snakeCoords[snakeCurrentSize - 1].x >= FRAME_BOT_RIGHT_X || snakeCoords[snakeCurrentSize - 1].x <= FRAME_UP_LEFT_X ||
		snakeCoords[snakeCurrentSize - 1].y >= FRAME_BOT_RIGHT_Y || snakeCoords[snakeCurrentSize - 1].y <= FRAME_UP_LEFT_Y){
		gameFlag = 1;
	}
	else if (snakeCurrentSize > 4){
		for (uint8_t i = 0; i < snakeCurrentSize - 4; i++){
			if(snakeCoords[i].x == snakeCoords[snakeCurrentSize - 1].x &&
			   snakeCoords[i].y == snakeCoords[snakeCurrentSize - 1].y){
				gameFlag = 1;
				break;
			}
		}
	}
	return gameFlag;
}

uint8_t game_win_check(void){
	if(snakeCurrentSize == SNAKE_SIZE_MAX){
		gameFlag = 2;
	}
	return gameFlag;
}

void draw_game_over(void){
	oledClearBuf();
	oledSetFont(FONT_12x16);
	oledPrintText("Game over!", 5, 20);
}

void draw_game_win(void){
	oledClearBuf();
	oledSetFont(FONT_12x16);
	oledPrintText("You win!", 15, 20);
}

void snake_set_direction(void){
	if (buttonsGetFlagNewVal() == true){
		uint8_t button = (uint8_t) buttonsGetCurrentBut();
		if (button != (uint8_t )VOID && button != (uint8_t) CENTER){
			if((button % 2) != (snakeDiriction % 2)) snakeDiriction = (buttons_t) button;
		}
	}
}

bool apple_eat(void){
	int8_t x_step = 0;
	int8_t y_step = 0;
	switch (snakeDiriction){
	case LEFT:
		x_step = -SNAKE_SIZE_PART;
		break;
	case RIGHT:
		x_step = SNAKE_SIZE_PART;
		break;
	case TOP:
		y_step = -SNAKE_SIZE_PART;
		break;
	case BOTTOM:
		y_step = SNAKE_SIZE_PART;
		break;
	default:
		break;
	}

	if((snakeCoords[snakeCurrentSize - 1].x + x_step) == appleCoords.x &&
	   (snakeCoords[snakeCurrentSize - 1].y + y_step) == appleCoords.y){
		snakeCoords[snakeCurrentSize].x = snakeCoords[snakeCurrentSize - 1].x + x_step;
		snakeCoords[snakeCurrentSize].y = snakeCoords[snakeCurrentSize - 1].y + y_step;
		snake_draw_part(snakeCoords[snakeCurrentSize].x, snakeCoords[snakeCurrentSize].y);
		snakeCurrentSize++;
		if (game_win_check() != 2){
			apple_spawn();
		}
		return true;
	}
	return false;
}

void snakeGame(void){
	if (gameFlag == 0) {
		snake_set_direction();
		if(apple_eat() == false){
			snake_move();
			gameFlag = crash_check();
		}
	}
	else{
		while (buttonsGetFlagNewVal() == false)chThdSleepMilliseconds(5);
		snake_start();
	}
	if (gameFlag == 1) draw_game_over();
	else if(gameFlag == 2) draw_game_win();
}
