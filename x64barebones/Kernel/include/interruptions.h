#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void iSetHandler(int index, uint64_t handler);
void sti();
void irq0Handler();
void irq1Handler();
void setPicMaster(uint16_t);
char _keyboard();

#endif