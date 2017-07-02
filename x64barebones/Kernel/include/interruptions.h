#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

#define TIME  0
#define READ  1
#define WRITE 2

// #define TIMER 100000000000



void iSetHandler(int index, uint64_t handler);
void setIDT();
void sti();
uint64_t irq0Handler();
uint64_t irq1Handler();
uint64_t irq2Handler();
uint64_t irq3Handler();
uint64_t irq4Handler();
uint64_t irq5Handler();
uint64_t irq6Handler();
uint64_t irq7Handler();
uint64_t irq8Handler();
uint64_t irq9Handler();
uint64_t irq10Handler();
uint64_t irq11Handler();
uint64_t irq12Handler();
uint64_t irq13Handler();
uint64_t irq14Handler();
uint64_t irq15Handler();
uint64_t irq80Handler();
void setPicMaster(uint16_t);
void setPicSlave(uint16_t);
void keyboard_init(void);
char read_port(unsigned short port);
void write_port(unsigned short port, unsigned char data);
void keyboard_handler(void);
void mouse_handler(void);
void systemCallHandler(int instruction, char * s, int sSize);
void initialize_Mouse(void);
void rewrite_CR3(void);
void displayModuleMsg(void);
int getOptionFromBuffer(void);
void change(void);
// void map_page(void * physicalAddress, void * virtualAddress);
void map_page(uint64_t physicalAddress);

#endif