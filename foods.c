/*###################################################################
#FileName：foods.c
#Author：liuxun
#Date：2022/07/05
#Describe：Null
#####################################################################*/

#include <stdlib.h>
#include "foods.h"
#include "winApi.h"
#include "greedySnakeMap.h"


void initFood(void)
{
	genFood();

	return;
}

void genFood(void)
{
	/*生成食物位置，数值修改保证食物不靠墙或嵌入墙体. */
	g_snakeFood.posx = rand() % (g_wall.width - 4) + g_wall.startX + 2;
	g_snakeFood.posy = rand() % (g_wall.height - 2)+ g_wall.startY + 1;

	//输出消息到消息框
	addMsg(MSG_GEN_FOOD);

	//画出食物
	setPos(g_snakeFood.posx, g_snakeFood.posy);
	printf("■");

	//把光标移出画面外
	setPos(g_map.width, g_map.height);

	return;
}