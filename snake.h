/*###################################################################
#FileName：snake.h
#Author：liuxun
#Date：2022/07/05
#Describe：Null
#####################################################################*/

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdbool.h>

#define DEFAULT_SNAKE_LEN 3
#define SNAKE_RUN_SPEED 400 //400ms
#define SNAKE_AGE_LIMIT	1000 //蛇身长度限制为1000
#define SNAKE_DEAD_WAIT 1200
#define HIT_WALL_MSG "Game Over!"
#define OUT_OF_AGE	"Snake Too Old!"
#define THANK_FOR_PLAY "THANK!"



typedef struct SGreedySnakeBody {
	int x;
	int y;
}SSnakeBody;

typedef struct SGreedySnake {
	int x;
	int y;
	int lenth;
	SSnakeBody body[SNAKE_AGE_LIMIT];
	int isAlive; //0:not alive, 1:alive
	int moveForce; //0:上 1:下 2:左 3:右
}SSnake;

SSnake g_snake;

void initSnake(void);
void moveSnake(void);
void drawSnake(void);
void runSnake(void);
int eatFood(void);
bool hitWall(void);
void DeadSnake(char* msg);

#endif
