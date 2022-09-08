/*###################################################################
#FileName£ºwinApi.h
#Author£ºliuxun
#Date£º2022/07/05
#Describe£ºNull
#####################################################################*/

#ifndef _WINAPI_H_
#define _WINAPI_H_

#define COLOR_BLACK 0x0
#define COLOR_YELLOW	0x6
#define COLOR_WHITE	0x7
#define COLOR_BLUE	0x9
#define COLOR_GREEN	0xa
#define COLOR_RED	0xc

void clearMap(void);
int setPos(int posx, int posy);
int getScreenSiz(int* width, int* height);
void setColor(int color);
void fullScreen(void);
void sleep(int time);
void beep(int a, int b);
void hidecursor(void);
#endif
