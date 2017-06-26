#ifndef _DRIVERVIDEO_H_
#define _DRIVERVIDEO_H_

#include <stdint.h>

#define ROWS 25
#define COLS 80

#define TIMER 100000000
#define CENTERED 54
#define CENTEREDCLICOS 20
#define MAX_INT 20
#define MAX_LONG 50
#define GMT 3
#define PIXEL 2
#define MOUSE 0x70
#define DEFAULTC 0x07
#define VIDSTART 0xB8000

void printOnScreenChar(char c);
void printOnScreen(char* string);
void clearScreen();
void myNewLine();
void welcomeMessage();
void shell();
void displayTime();
int _sysTime(int date);
void backspace(int newline);
void scroll(void);
char* longToChar(unsigned long n);
void draw_pixel(int x, int y, int color);

#endif