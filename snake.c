/*###################################################################
#FileName：snake.c
#Author：liuxun
#Date：2022/07/05
#Describe：Null
#####################################################################*/

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "snake.h"
#include "greedySnakeMap.h"
#include "winApi.h"
#include "foods.h"

//"▲"
void initSnake()
{
	srand((unsigned int)time(NULL));
	g_snake.x = rand() % (g_wall.width - g_snake.lenth * 2) + g_wall.startX ; //因为方块宽度为2，所以*2
	g_snake.y = rand() % (g_wall.height - g_snake.lenth) + g_wall.startY;

	g_snake.lenth = DEFAULT_SNAKE_LEN;
	g_snake.isAlive = 1;
	g_snake.moveForce = rand() % 4;

	//按随机方向展示蛇位置
	if (g_snake.moveForce == 0) {
		//横向
		g_snake.body[0].x = g_snake.x + 2;
		g_snake.body[0].y = g_snake.y;

		for (int i = 1; i < g_snake.lenth; i++) {
			g_snake.body[i].x = g_snake.body[i - 1].x + 2;
			g_snake.body[i].y = g_snake.body[i - 1].y;
		}
	}
	else {
		//纵向
		g_snake.body[0].x = g_snake.x;
		g_snake.body[0].y = g_snake.y + 1;

		for (int i = 1; i < g_snake.lenth; i++) {
			g_snake.body[i].x = g_snake.body[i - 1].x;
			g_snake.body[i].y = g_snake.body[i - 1].y + 1;
		}
	}

	drawSnake();
}

void moveSnake()
{
	//清理蛇尾巴
	setPos(g_snake.body[g_snake.lenth - 1].x, g_snake.body[g_snake.lenth - 1].y);
	printf("  ");
	setPos(g_map.width, g_map.height);

	for (int i = g_snake.lenth - 1; i >= 0; i--)
	{
		g_snake.body[i].x = g_snake.body[i - 1].x;
		g_snake.body[i].y = g_snake.body[i - 1].y;
	}

	g_snake.body[0].x = g_snake.x;
	g_snake.body[0].y = g_snake.y;

	if (g_snake.moveForce == 0) {
		g_snake.y--;
	}
	else if (g_snake.moveForce == 1){
		g_snake.y++;
	}
	else if(g_snake.moveForce == 2) {
		g_snake.x = g_snake.x - 2; //左右移动时，因为方块宽度为2，所以移动两格
	}
	else {
		g_snake.x = g_snake.x + 2;//左右移动时，因为方块宽度为2，所以移动两格
	}

	return;
}

void drawSnake()
{
	setPos(g_snake.x, g_snake.y);
	printf("●");

	for (int i = 0; i < g_snake.lenth; i++) {
		setPos(g_snake.body[i].x, g_snake.body[i].y);
		printf("■");
	}

	setPos(g_map.width, g_map.height);
	return;
}

void runSnake() 
{
	int flag;
	bool changeDir = false;
	while (1) {
		if (kbhit()) {
			flag = getch();
			changeDir = true;
			if (flag == 224) flag = getch();
			if (flag == 72 && g_snake.moveForce != 1) {
				g_snake.moveForce = 0;
				addMsg(MSG_MOVE_UP);
			}
			if (flag == 80 && g_snake.moveForce != 0) {
				g_snake.moveForce = 1;
				addMsg(MSG_MOVE_DOWN);
			}
			if (flag == 75 && g_snake.moveForce != 3) {
				g_snake.moveForce = 2;
				addMsg(MSG_MOVE_LEFT);
			}
			if (flag == 77 && g_snake.moveForce != 2) {
				g_snake.moveForce = 3;
				addMsg(MSG_MOVE_RIGHT);
			}
		}

		if (changeDir == false) {
			sleep(SNAKE_RUN_SPEED);
		}
		else {
			changeDir = false;
		}

		//蛇移动并判断是否撞墙
		moveSnake();
		if (hitWall() == true) {
			break;
		}

		//吃食物，失败则退出
		if (eatFood() != 0) {
			break;
		}

		//移动并做觅食判断后，重绘蛇身
		drawSnake();

		//刷新成绩
		showScore();

	}
}

/*0:正常吃食物 -1:太长，不能再吃了 */
int eatFood(void)
{
	if ( abs(g_snake.x - g_snakeFood.posx) <= 1 && g_snake.y == g_snakeFood.posy) {
		setPos(g_snakeFood.posx, g_snakeFood.posy);
		printf("  ");
		beep(700, 800);
		//蛇长大一个单位
		for (int i = g_snake.lenth; i > 0; i--) {
			g_snake.body[i].x = g_snake.body[i - 1].x;
			g_snake.body[i].y = g_snake.body[i - 1].y;
		}
		g_snake.body[0].x = g_snake.x;
		g_snake.body[0].y = g_snake.y;
		g_snake.x = g_snakeFood.posx;
		g_snake.y = g_snakeFood.posy;
		g_snake.lenth++;

		//加分
		g_scoreBox.curScore++;

		//输出消息到消息框
		addMsg(MSG_SNAKE_EAT_FOOD);
		
		if (g_snake.lenth >= SNAKE_AGE_LIMIT) {
			//限制蛇长度，超过则自动消亡
			DeadSnake(OUT_OF_AGE);

			//输出信息到消息框
			addMsg(MSG_SNAKE_TOO_LOOG);
			sleep(SNAKE_DEAD_WAIT);

			return -1;
		}

		genFood();
	}

	setPos(g_map.width, g_map.height);

	return 0;
}

bool waitToAlive()
{
	int flag;
	while (1) {
		if (kbhit()) {
			flag = getch();
			if (flag == 'r' || flag == 'R') {
				return true;
			}
			else if (flag == 'z' || flag == 'Z') {
				return false;
			}
		}
	}

	return false;
}

void DeadSnake(char* msg)
{
	g_snake.isAlive = 0;
	g_snake.lenth = 0;
	clearMap();
	showMap();

	setPos(g_wall.startX + g_wall.width / 2 - sizeof(msg), g_wall.startY + g_wall.height / 2);
	setColor(COLOR_RED);
	printf("%s", msg);
	setColor(COLOR_WHITE);
	setPos(0, g_wall.startY + g_wall.height + 1);

	if (waitToAlive() == true) {//alive
		clearMap();
		g_scoreBox.curScore = 0;
		g_scoreBox.round++;
		showMap();
		initSnake();
		initFood();
		runSnake();
	}
	else {//absolutly dead
		msg = THANK_FOR_PLAY;
		clearMap();
		setPos(g_wall.startX + g_wall.width / 2 - sizeof(msg), g_wall.startY + g_wall.height / 2);
		setColor(COLOR_GREEN);
		printf("%s", msg);
		setColor(COLOR_WHITE);
		setPos(0, g_wall.startY + g_wall.height + 1);
	}

	return;
}

bool hitWall(void)
{
	bool ret = false;

	if (g_snake.x >= (g_wall.startX + g_wall.width)
		|| g_snake.x <= g_wall.startX
		|| g_snake.y >= (g_wall.startY + g_wall.height)
		|| g_snake.y <= g_wall.startY
		)
	{
		ret = true;
		beep(200, 1000);
		addMsg(MSG_SNAKE_HIT_WALL);
		sleep(SNAKE_DEAD_WAIT);
		DeadSnake(HIT_WALL_MSG);
	}

	return ret;
}