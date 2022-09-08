/*###################################################################
#FileName£ºdraw.c
#Author£ºliuxun
#Date£º2022/07/05
#Describe£ºNull
#####################################################################*/

#include <stdio.h>
#include "draw.h"
#include "greedySnakeMap.h"
#include "errorCode.h"
#include "winApi.h"
#include "snake.h"


int main(int argc, char* argv[])
{
	fullScreen();
	initMap();
	initSnake();
	initFood();
	runSnake();

	return 0;
}



