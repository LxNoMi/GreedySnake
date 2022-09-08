/*###################################################################
#FileName：winApi.c
#Author：liuxun
#Date：2022/07/05
#Describe：Null
#####################################################################*/

#include "winapi.h"
#include <windows.h>
#include "errorCode.h"

void clearMap()
{
	system("CLS");

	return;
}

void sleep(int time)
{
	Sleep(time);

	return;
}

void beep(int a, int b)
{
	Beep(a, b);

	return;
}

void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

	return;
}

int setPos(int posx, int posy)
{
	HANDLE hOut;
	COORD pos = { posx, posy };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);

	return RET_OK;
}

int getScreenSiz(int* width, int* height)
{
	*width = 190;
	*height = 60;

	return RET_OK;
}

void setColor(int color)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, color);

	return;
}

void fullScreen()
{
	HWND hwnd = GetForegroundWindow();
	int x = GetSystemMetrics(SM_CXSCREEN);            //屏幕宽度 像素 
	int y = GetSystemMetrics(SM_CYSCREEN);            //屏幕高度 像素
	LONG winStyle = GetWindowLong(hwnd, GWL_STYLE);   //获取窗口信息

	//设置窗口信息 最大化 取消标题栏及边框
	SetWindowLong(hwnd, GWL_STYLE, (winStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, x, y, 0);

	return;
}