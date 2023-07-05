#include "snake.h"
#include "terminal_write.h"

static snakePartsCoord snakeCoords[2] = {
	{.x = 0,
	.y = 0},
	{.x = 0,
	.y = 0}
};


static uint8_t snakeCurrentSize = 0;


void snake_draw_part(uint8_t x, uint8_t y){
	oledDrawRect(x, y, x + SNAKE_SIZE_BLOCK - 1, y + SNAKE_SIZE_BLOCK - 1, true);
}

void snakeInit(void){
	oledInit();

	oledDrawRect(FRAME_UP_LEFT_X, FRAME_UP_LEFT_Y, FRAME_BOT_RIGHT_X, FRAME_BOT_RIGHT_Y, false);
	oledDrawRect(FRAME_UP_LEFT_X - 1, FRAME_UP_LEFT_Y - 1, FRAME_BOT_RIGHT_X + 1, FRAME_BOT_RIGHT_Y + 1, false);

	snakeCoords[1].x = 6;
	snakeCoords[1].y = 32;
	snakeCoords[0].x = snakeCoords[1].x + 2 * SNAKE_SIZE_PART;
	snakeCoords[0].y = 32;
	snake_draw_part(snakeCoords[0].x, snakeCoords[0].y);
	snake_draw_part(snakeCoords[1].x, snakeCoords[1].y);
	snake_draw_part(snakeCoords[1].x + SNAKE_SIZE_PART, snakeCoords[0].y);

	snakeCurrentSize = 3;

	oledUpdatePic();
}

void snake_clear_last_part(void){
	oledSetColorDraw(COLOR_BLACK);
	oledDrawRect(snakeCoords[1].x, snakeCoords[1].y,
	snakeCoords[1].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[1].y + SNAKE_SIZE_BLOCK - 1, true);
	oledSetColorDraw(COLOR_WHITE);
}


void snakeMove(void){
	snake_clear_last_part();
	snakeCoords[1].x += SNAKE_SIZE_PART;
	snakeCoords[0].x += SNAKE_SIZE_PART;
	oledDrawRect(snakeCoords[0].x, snakeCoords[0].y,
	snakeCoords[0].x + SNAKE_SIZE_BLOCK - 1, snakeCoords[0].y + SNAKE_SIZE_BLOCK - 1, true);
}

//void snakeGame(void){
// snakeMove();
// if
//}
