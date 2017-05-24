#ifndef _DRIVERVIDEO_H_
#define _DRIVERVIDEO_H_

#include <stdint.h>

void printOnScreen(char* string);
void clearScreen();
void myNewLine();
void welcomeMessage();
void shell();
void displayTime();
int _sysTime(int date);

#endif