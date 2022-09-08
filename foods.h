/*###################################################################
#FileName£ºfoods.h
#Author£ºliuxun
#Date£º2022/07/05
#Describe£ºNull
#####################################################################*/

#ifndef _FOODS_H_
#define _FOODS_H_

typedef struct SGreedySnakeFood {
	int posx;
	int posy;
}SSnakeFood;

SSnakeFood g_snakeFood;
void initFood(void);
void genFood(void);

#endif
