/*###################################################################
#FileName£ºgreedySnakeMap.h
#Author£ºliuxun
#Date£º2022/07/05
#Describe£ºNull
#####################################################################*/

#ifndef __GREEDYSNAKEMAP_H_
#define __GREEDYSNAKEMAP_H_

#define MAX_MSG_NUM 3
#define MAX_FORWARD_NUM 6
#define MSG_GAME_START "Game start!"
#define MSG_GAME_END "Game over!"
#define MSG_SNAKE_HIT_WALL "Snake hit the wall!"
#define MSG_SNAKE_TOO_LOOG "Snake too loog!"
#define MSG_SNAKE_EAT_FOOD "Snake eat food!"
#define MSG_GEN_FOOD "Generate a food!"
#define MSG_MOVE_UP "Snake move up!"
#define MSG_MOVE_DOWN "Snake move down!"
#define MSG_MOVE_LEFT "Snake move left!"
#define MSG_MOVE_RIGHT "Snake move right!"

typedef struct SGreedySnakeMap{
	int height;
	int width;
}SMap;

typedef struct SGreedySnakeWall {
	int startX;
	int startY;
	int width;
	int height;
}SWall;

typedef struct SGreedySnakeTitle {
	int startX;
	int startY;
	char title[20];
}STitle;

typedef struct SGreedySnakeMsgBox {
	int startX;
	int startY;
	int count;
	char* msgs[MAX_MSG_NUM];
}SMsgBox;

typedef struct SGreedySnakeForwardBox {
	int startX;
	int startY;
	int count;
	char* forwardEntry[MAX_FORWARD_NUM];
}SForwardBox;

typedef struct SGreedySnakeScoreBox {
	int startX;
	int startY;
	int round;
	int curScore;
	int rank;
}SScoreBox;

SMap g_map;
SWall g_wall;
STitle g_title;
SMsgBox g_msgBox; 
SScoreBox g_scoreBox;
SForwardBox g_forwardBox;


extern int initMap(void);
extern void showMap(void);
extern void showScore(void);
extern void showTitle(void);
extern void showWall(void);
extern void showMsg(void);
extern void addMsg(char* msg);

#endif
