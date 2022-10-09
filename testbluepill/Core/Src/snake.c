//#include "stm32f1xx_hal.h"
#include "snake.h"

void SnakeUpdatePos(void)
{
	for (uint16_t i = snakeCount; i >= 1; i--) {
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	snake[0].x += vx;
	snake[0].y += vy;


	if(snake[0].x > FIELDSIZE){
		snake[0].x = 0;
	}
}

void SnakeCheckApple(void)
{
	if(snake[0].x == apple.x && snake[0].y == apple.y){
		snakeCount += 1;
		snake[snakeCount].x = snake[0].x;
			snake[snakeCount].y = snake[0].y;
			apple.x = rand()%FIELDSIZE;
			apple.y = rand()%FIELDSIZE;
	}

}
void SnakeDraw(void)
{
	BUF_PushColor(buf, BUF_SIZE, TFT9341_CYAN);
	for (uint16_t i = 0; i < snakeCount; i++) {
		TFT9341_DrawRect(buf, snake[i].x * CELLSIZE, snake[i].y * CELLSIZE,
				snake[i].x * CELLSIZE + CELLSIZE - 1,
				snake[i].y * CELLSIZE + CELLSIZE - 1);
	}
	BUF_PushColor(buf2, BUF_SIZE, TFT9341_RED);
	TFT9341_DrawRect(buf2, apple.x * CELLSIZE, apple.y * CELLSIZE, apple.x * CELLSIZE + CELLSIZE-1, apple.y * CELLSIZE +CELLSIZE-1);
}
void SnakeClear(void){
	for (uint16_t i = 0; i < snakeCount; i++) {
			TFT9341_FillRect(snake[i].x * CELLSIZE, snake[i].y * CELLSIZE,
					snake[i].x * CELLSIZE + CELLSIZE - 1,
					snake[i].y * CELLSIZE + CELLSIZE - 1, TFT9341_WHITE);
		}
}
void SnakeMain(void)
{
	snakeCount = 8;
	apple.x = 8;
	apple.y = 8;
	vx = 1;
	srand(10);
	//SnakeReset();
	while (1) {
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET){
			vy = 1;
		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET){
			vy = -1;
		}

		if(timFlag == 1){
			SnakeClear();
			SnakeUpdatePos();
			SnakeDraw();
			SnakeCheckApple();
			timFlag = 0;
		}
	}
}
