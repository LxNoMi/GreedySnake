/*###################################################################
#FileName：greedySnakeMap.c
#Author：liuxun
#Date：2022/07/05
#Describe：Null
#####################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include "greedySnakeMap.h"
#include "errorCode.h"
#include "winApi.h"
#include "foods.h"
#include "snake.h"

void showWall(void)
{
	//画上下边界
	for (int i = g_wall.startX; i < g_wall.startX + g_wall.width; i++) {
		setPos(i, g_wall.startY);
		printf("█");
		setPos(i, g_wall.startY + g_wall.height);
		printf("█");
	}

	//画左右边界
	for (int i = g_wall.startY; i < g_wall.startY + g_wall.height; i++) {
		setPos(g_wall.startX, i);
		printf("▋");
		setPos(g_wall.startX + g_wall.width, i);
		printf("▋");
	}
	setPos(g_map.width, g_map.height);

	return;
}

int initWall(int startx, int starty, int width, int height)
{
	g_wall.startX = startx;
	g_wall.startY = starty;
	g_wall.width = width;
	g_wall.height = height;

	showWall();

	return RET_OK;
}

void showTitle(void)
{
	setPos(g_title.startX, g_title.startY);
	printf("%s", g_title.title);

	setPos(g_map.width, g_map.height);

	return;
}

int initTitle(int startx, int starty, char* title)
{
	g_title.startX = startx;
	g_title.startY = starty;
	strcpy(g_title.title, title);
	showTitle();

	return RET_OK;
}

void showScore()
{
	setPos(g_scoreBox.startX, g_scoreBox.startY);
	printf("轮次:%d", g_scoreBox.round);

	setPos(g_scoreBox.startX, g_scoreBox.startY + 2);
	printf("得分:%d", g_scoreBox.curScore);

	setPos(g_scoreBox.startX, g_scoreBox.startY + 4);
	printf("排名:%d", g_scoreBox.rank);

	setPos(g_map.width, g_map.height);

	return;
}

int initScore(int startx, int starty)
{
	g_scoreBox.startX = startx;
	g_scoreBox.startY = starty;
	g_scoreBox.round = 1;
	g_scoreBox.curScore = 0;
	g_scoreBox.rank = 1;

	showScore();

	return RET_OK;
}

void showMsg()
{
	for (int i = 0; i < g_msgBox.count; i++) {
		setPos(g_msgBox.startX, g_msgBox.startY + i);
		printf("                                  ");
		setPos(g_msgBox.startX, g_msgBox.startY + i);
		printf("%s", g_msgBox.msgs[i]);
	}

	setPos(g_map.width, g_map.height);

	return;
}

int initMsg(int startx, int starty)
{
	g_msgBox.startX = startx;
	g_msgBox.startY = starty;
	g_msgBox.count = 1;

	g_msgBox.msgs[0] = MSG_GAME_START;

	for (int i = 1; i < MAX_MSG_NUM; i++) {
		g_msgBox.msgs[i] = "";
	}

	showMsg();

	return RET_OK;
}

void showForward()
{
	for (int i = 0; i < g_forwardBox.count; i++) {
		setPos(g_forwardBox.startX, g_forwardBox.startY + 2*i);
		printf("%s", g_forwardBox.forwardEntry[i]);
	}

	setPos(g_map.width, g_map.height);

	return;
}

int initFoerwardBox(int startx, int starty)
{
	g_forwardBox.startX = startx;
	g_forwardBox.startY = starty;
	g_forwardBox.forwardEntry[0] = "上移:▲";
	g_forwardBox.forwardEntry[1] = "下移:▼";
	g_forwardBox.forwardEntry[2] = "左移:<";
	g_forwardBox.forwardEntry[3] = "右移:>";
	g_forwardBox.forwardEntry[4] = "复活:R";
	g_forwardBox.forwardEntry[5] = "结束:Z";
	g_forwardBox.count = MAX_FORWARD_NUM;

	showForward();

	return RET_OK;
}

int initMap()
{
	//获取屏幕大小
	getScreenSiz(&g_map.width, &g_map.height);
	initTitle((int)(g_map.width * 0.5), (int)(g_map.height * 0.05), "贪吃蛇");
	initWall((int)(g_map.width * 0.1), (int)(g_map.height * 0.1), (int)(g_map.width * 0.8), (int)(g_map.height * 0.8));
	initScore(g_wall.startX + g_wall.width + 2, g_wall.startY + g_wall.height * 0.2);
	initMsg(g_wall.startX, g_wall.startY + g_wall.height + 1);
	initFoerwardBox(g_wall.startX - 7, g_wall.startY + g_wall.height * 0.1);
	hidecursor();

	return RET_OK;
}


void showMap(void)
{
	showTitle();
	showWall();
	showScore();
	showMsg();
	showForward();

	return;
}

void addMsg(char* msg)
{
	if (g_msgBox.count < MAX_MSG_NUM) {
		g_msgBox.msgs[g_msgBox.count] = msg;
		g_msgBox.count++;
	}
	else {
		for (int i = 0; i < g_msgBox.count - 1; i++) {
			g_msgBox.msgs[i] = g_msgBox.msgs[i + 1];
		}
		g_msgBox.msgs[g_msgBox.count - 1] = msg;
	}

	showMsg();

	return;
}

