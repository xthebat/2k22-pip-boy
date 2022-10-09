#include "stm32f1xx_hal.h"
#include "spi_ili9341.h"
#include <stdio.h>
struct cell{
	int8_t x;
	int8_t y;
};
#define SNAKESIZE 20
#define FIELDSIZE 16
#define CELLSIZE 10

struct cell snake[SNAKESIZE];
struct cell apple;
int8_t vx,vy;
uint8_t snakeCount;
uint8_t timFlag;
#define SnakeReset() snakeCount = 1


void SnakeCheckApple(void);
void SnakeDraw(void);
void SnakeMain(void);

