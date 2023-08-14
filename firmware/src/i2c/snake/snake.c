#include "snake.h"
#include "terminal_write.h"

static snakePartsCoord snakeCoords[SNAKE_SIZE_MAX] = {
	{.x = 0, .y = 0}
};

static snakePartsCoord appleCoords = {
	.x = 0, .y = 0
};

static buttons_t snakeDiriction = RIGHT;

static uint8_t snakeCurrentSize = 0;

static bool crashFlag = false;


void snake_draw_part(uint8_t x, uint8_t y){
	oledDrawRect(x, y, x + SNAKE_SIZE_BLOCK - 1, y + SNAKE_SIZE_BLOCK - 1, true);
}

void apple_draw(uint8_t x, uint8_t y){
	oledDrawLineCoord(x + 1, y, x + 2, y);
	oledDrawLineCoord(x, y + 1, x + 3, y + 1);
	oledDrawLineCoord(x, y + 2, x + 3, y + 2);
	oledDrawLineCoord(x + 1, y + 3, x + 2, y + 3);
}

void apple_spawn(void){
	uint8_t x, y;
	bool flag = false;
	while(!flag){
		y = rand() % 9;
		x = rand() % 20;

		x = x * SNAKE_SIZE_PART + 4;
		y = y * SNAKE_SIZE_PART + 4;

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

	apple_draw(appleCoords.x, appleCoords.y);
}

void snake_start(void){
	oledDrawRect(FRAME_UP_LEFT_X, FRAME_UP_LEFT_Y, FRAME_BOT_RIGHT_X, FRAME_BOT_RIGHT_Y, false);
	oledDrawRect(FRAME_UP_LEFT_X - 1, FRAME_UP_LEFT_Y - 1, FRAME_BOT_RIGHT_X + 1, FRAME_BOT_RIGHT_Y + 1, false);

	for (uint8_t i = 0; i < SNAKE_SIZE_MAX; i++){
		snakeCoords[i].x = 0;
		snakeCoords[i].y = 0;
	}

	snakeCurrentSize = 7;
	for (uint8_t i = 0; i < snakeCurrentSize; i++){
		snakeCoords[i].x = 4 + i * SNAKE_SIZE_PART;
		snakeCoords[i].y = 4;
		snake_draw_part(snakeCoords[i].x, snakeCoords[i].y);
	}

	oledUpdatePic();
	while (buttonsGetFlagNewVal() == false)chThdSleepMilliseconds(5);
	srand((uint32_t) chVTGetSystemTime());
}

void snakeInit(void){
	oledInit();

	buttonsInit();
	chThdSleepMilliseconds(5);
	snake_start();
	apple_spawn();
	oledUpdatePic();
}

void snake_clear_last_part(void){
	oledSetColorDraw(COLOR_BLACK);
	oledDrawRect(snakeCoords[0].x, snakeCoords[0].y,
				 snakeCoords[0].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[0].y + SNAKE_SIZE_BLOCK - 1, true);
	oledSetColorDraw(COLOR_WHITE);
}


void snake_move(void){

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

	if (snakeCoords[snakeCurrentSize - 1].x == appleCoords.x &&
		snakeCoords[snakeCurrentSize - 1].y == appleCoords.y){
		snakeCurrentSize++;
	}
	else{
		snake_clear_last_part();
	}
}

bool crash_check(void){
	if (snakeCoords[snakeCurrentSize - 1].x >= FRAME_BOT_RIGHT_X || snakeCoords[snakeCurrentSize - 1].x <= FRAME_UP_LEFT_X ||
		snakeCoords[snakeCurrentSize - 1].y >= FRAME_BOT_RIGHT_Y || snakeCoords[snakeCurrentSize - 1].y <= FRAME_UP_LEFT_Y){
		crashFlag = true;
	}
	else if (snakeCurrentSize > 4){
		for (uint8_t i = 0; i < snakeCurrentSize - 4; i++){
			if(snakeCoords[i].x == snakeCoords[snakeCurrentSize - 1].x &&
			   snakeCoords[i].y == snakeCoords[snakeCurrentSize - 1].y){
				crashFlag = true;
				break;
			}
		}
	}
	return crashFlag;
}

void draw_game_over(void){
	oledClearBuf();
	oledSetFont(FONT_12x16);
	oledPrintText("Game over!", 5, 20);
}

void snake_set_direction(void){
	if (buttonsGetFlagNewVal() == true){
		uint8_t button = (uint8_t) buttonsGetCurrentBut();
		if (button != (uint8_t )VOID && button != (uint8_t) CENTER){
			if((button % 2) != (snakeDiriction % 2)) snakeDiriction = (buttons_t) button;
		}
	}
}

//void apple_eat(void){
//
//}

void snakeGame(void){
	if (crashFlag == false) {
		snake_set_direction();
		snake_move();
		crashFlag = crash_check();
	}
	if (crashFlag == true) draw_game_over();
}
