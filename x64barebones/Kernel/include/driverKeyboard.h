#ifndef _DRIVERKEYBOARD_H_
#define _DRIVERKEYBOARD_H_

#define MAX_KEYPRESSED 60

void keyboard_handler(void);
void cpyToBuffer(char * s);
void cpyFromBuffer(char * s);
char getCharFromBuffer(void);

#endif