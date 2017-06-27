#ifndef _DRIVERMOUSE_H_
#define _DRIVERMOUSE_H_

void initialize_Mouse(void);
void mouse_wait(unsigned char type);
void mouse_write(unsigned char a_write);
unsigned char mouse_read();
void mouse_handler();
void printCursor(uint8_t mouseCoord_x, uint8_t mouseCoord_y, char leftClick);

#endif