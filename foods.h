/*###################################################################
#FileName��foods.h
#Author��liuxun
#Date��2022/07/05
#Describe��Null
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
