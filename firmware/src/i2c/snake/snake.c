#include "snake.h"
#include "terminal_write.h"


// Coordinates of all parts of the snake.
static coords_t snakeCoords[SNAKE_SIZE_MAX] = {
	{.x = 0, .y = 0}
};

// Apple coordinates.
static coords_t appleCoords = {
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
 * @brief	Initializes the start position of the snake.
 *
 * @note	Resets all params.
 *
 * @notapi
 */
void snake_start(void){
	oledClearBuf(); // Cleaqr the screen.

	// Resets params.
	gameFlag = READY;
	snakeDiriction = RIGHT;

	for (uint8_t i = 0; i < SNAKE_SIZE_MAX; i++){
		snakeCoords[i].x = 0;
		snakeCoords[i].y = 0;
	}

	snakeCurrentSize = SNAKE_SIZE_INIT;

	// Draw the frame.
	oledDrawRect(FRAME_UP_LEFT_X, FRAME_UP_LEFT_Y, FRAME_BOT_RIGHT_X, FRAME_BOT_RIGHT_Y, false);
	oledDrawRect(FRAME_UP_LEFT_X - 1, FRAME_UP_LEFT_Y - 1, FRAME_BOT_RIGHT_X + 1, FRAME_BOT_RIGHT_Y + 1, false);

	// Draw initial snake.
	for (uint8_t i = 0; i < snakeCurrentSize; i++){
		snakeCoords[i].x = 4 + i * SNAKE_SIZE_PART;
		snakeCoords[i].y = 28;
		snake_draw_part(snakeCoords[i].x, snakeCoords[i].y);
	}

	oledUpdatePic(); // Sends the buffer to the display.
}


/*
 * @brief	Removes the last snake element from the screen.
 *
 * @note	Does not remove the last element from the array.
 *
 * @note	To make it look like the snake is moving.
 *
 * @notapi
 */
void snake_clear_last_part(void){
	oledSetColorDraw(COLOR_BLACK);
	oledDrawRect(snakeCoords[0].x, snakeCoords[0].y,
				 snakeCoords[0].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[0].y + SNAKE_SIZE_BLOCK - 1, true);
	oledSetColorDraw(COLOR_WHITE);
}

/*
 * @brief	Moves the snake by one square.
 *
 * @note	The direction of movement is determined by the last button pressed.
 *
 * @note	Do not change enum with the diruction of movement!
 * 			Can lead to errors.
 *
 * @notapi
 */
void snake_move(void){
	snake_clear_last_part(); // Remove the last part of the snake.

	// Step by coordinates on which the snake will move depending on the pressed button.
	int8_t x_step = 0;
	int8_t y_step = 0;

	// Where to move.
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

	// Moves the coordinates of the snake parts one step forward.
	for (uint8_t i = 0; i < snakeCurrentSize - 1; i++){
		snakeCoords[i].x = snakeCoords[i + 1].x;
		snakeCoords[i].y = snakeCoords[i + 1].y;
	}
	snakeCoords[snakeCurrentSize - 1].x = snakeCoords[snakeCurrentSize - 2].x + x_step;
	snakeCoords[snakeCurrentSize - 1].y = snakeCoords[snakeCurrentSize - 2].y + y_step;

	// Draw new part of the snake.
	oledDrawRect(snakeCoords[snakeCurrentSize - 1].x, snakeCoords[snakeCurrentSize - 1].y,
				 snakeCoords[snakeCurrentSize - 1].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[snakeCurrentSize - 1].y + SNAKE_SIZE_BLOCK - 1, true);
}

/*
 * @brief	Check for game over.
 *
 * @param_out	gameFlag	Game status (READY, LOSE, WIN).
 *
 * @notapi
 */
uint8_t crash_check(void){
	// Crash into frames.
	if (snakeCoords[snakeCurrentSize - 1].x >= FRAME_BOT_RIGHT_X || snakeCoords[snakeCurrentSize - 1].x <= FRAME_UP_LEFT_X ||
		snakeCoords[snakeCurrentSize - 1].y >= FRAME_BOT_RIGHT_Y || snakeCoords[snakeCurrentSize - 1].y <= FRAME_UP_LEFT_Y){
		gameFlag = LOSE;
	}
	// Crash into parts of the snake.
	else if (snakeCurrentSize > 4){
		for (uint8_t i = 0; i < snakeCurrentSize - 4; i++){
			if(snakeCoords[i].x == snakeCoords[snakeCurrentSize - 1].x &&
			   snakeCoords[i].y == snakeCoords[snakeCurrentSize - 1].y){
				gameFlag = LOSE;
				break;
			}
		}
	}
	return gameFlag;
}

/*
 * @brief	Check for win.
 *
 * @param_out	gameFlag	Game status (READY, LOSE, WIN).
 *
 * @notapi
 */
uint8_t game_win_check(void){
	if(snakeCurrentSize == SNAKE_SIZE_MAX){
		gameFlag = WIN;
	}
	return gameFlag;
}

/*
 * @brief	Draw "Game over!".
 *
 * @notapi
 */
void draw_game_over(void){
	oledClearBuf();
	oledSetFont(FONT_12x16);
	oledPrintText("Game over!", 5, 20);
}

/*
 * @brief	Draw "You win!".
 *
 * @notapi
 */
void draw_game_win(void){
	oledClearBuf();
	oledSetFont(FONT_12x16);
	oledPrintText("You win!", 15, 20);
}

/*
 * @brief	Set the direction of movement by the last button pressed.
 *
 * @note	Does not change direction if you press the opposite button.
 *
 * @note	Do not change enum with the diruction of movement!
 * 			Can lead to errors.
 *
 * @notapi
 */
void snake_set_direction(void){
	if (buttonsGetFlagNewVal() == true){ // Button was pressed.
		uint8_t button = (uint8_t) buttonsGetCurrentBut();
		if (button != (uint8_t )VOID && button != (uint8_t) CENTER){
			if((button % 2) != (snakeDiriction % 2)) snakeDiriction = (buttons_t) button; // Check for opposite button.
		}
	}
}

/*
 * @brief	Checking for eating an apple by the snake.
 *
 * @param_out	true	The snake ate the apple.
 * 				false	The snake didn't eat the apple.
 *
 * @notapi
 */
bool apple_eat(void){
	// Step by coordinates on which the snake will move depending on the pressed button.
	int8_t x_step = 0;
	int8_t y_step = 0;

	// Where to move.
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
	   (snakeCoords[snakeCurrentSize - 1].y + y_step) == appleCoords.y){ // Ate the apple.
		// Draw new part.
		snakeCoords[snakeCurrentSize].x = snakeCoords[snakeCurrentSize - 1].x + x_step;
		snakeCoords[snakeCurrentSize].y = snakeCoords[snakeCurrentSize - 1].y + y_step;
		snake_draw_part(snakeCoords[snakeCurrentSize].x, snakeCoords[snakeCurrentSize].y);
		snakeCurrentSize++; // Increase lenght of the snake.

		// Check for win.
		if (game_win_check() != WIN){
			apple_spawn();
		}
		return true;
	}
	return false;
}


/*
 * @brief	Inits the snake game.
 *
 * @note	Inits buttons to play.
 *
 * @note	Inits the oled display.
 */
void snakeInit(void){
	oledInit(); // inits the oled display.

	buttonsInit(); // Inits the button.
	chThdSleepMilliseconds(5);

	snake_start(); // Initializes the start position of the snake.

	// Waiting for a button press to start the game.
	while (buttonsGetFlagNewVal() == false)chThdSleepMilliseconds(5);

	srand((uint32_t) chVTGetSystemTime()); // Init random.

	apple_spawn(); // Spawns the apple.

	oledUpdatePic(); // Sends the buffer to the display.
}


/*
 * @brief	Makes one move of the snake and checks for the result (Main game);
 *
 * @note	Use in a loop!
 */
void snakeGame(void){
	if (gameFlag == READY) { // In a game.
		snake_set_direction(); // Set the direction of movement by the last button pressed.
		if(apple_eat() == false){ // The snake didn't eat the apple.
			snake_move(); // Moves the snake by one square.
			gameFlag = crash_check(); // Check for game over.
		}
	}
	else{ // Not in a game.
		// Waiting for a button press to start the game.
		if (buttonsGetFlagNewVal() == true){
			snake_start(); // Initializes the start position of the snake.

			apple_spawn(); // Spawns the apple.

			oledUpdatePic(); // Sends the buffer to the display.
		}
	}
	if (gameFlag == LOSE) draw_game_over(); // Draw "Game over!".
	else if(gameFlag == WIN) draw_game_win(); // Draw "You win!".
}
