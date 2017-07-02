#ifndef _SYSTEMCALLS_H_
#define _SYSTEMCALLS_H_

#include <stdint.h>

#define TIME  0
#define READ  1
#define WRITE 2

uint64_t read(char * s, int sSize);
// uint64_t read(char * s);
uint64_t write(char * s);
uint64_t time();
uint64_t systemCall(uint64_t instruction, uint64_t sSize, uint64_t str);

#endif