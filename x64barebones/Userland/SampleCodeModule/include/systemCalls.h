#ifndef _SYSTEMCALLS_H_
#define _SYSTEMCALLS_H_

#define TIME  0
#define READ  1
#define WRITE 2

uint64_t read(int fd, char * s, int sSize);
uint64_t write(int fd, char * s, int sSize);
uint64_t time(int fd, char * s, int sSize);

#endif