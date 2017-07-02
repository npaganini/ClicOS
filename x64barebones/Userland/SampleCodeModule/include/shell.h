#ifndef _SHELL_H_
#define _SHELL_H_

int shell(void);
void getInput(void);
int processCommand(void);
void helpMenu(void);
void clear(void);
void showCurrTime(void);
void echo(char * s);
void clearShellBuffer(void);

#endif