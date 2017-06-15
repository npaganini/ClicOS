#include "include/systemCalls.h"

uint64_t read(int fd, char * s, int sSize) {
	return systemCall(READ, fd, sSize, (uint64_t) s);
}

uint64_t write(int fd, char * s, int sSize) {
	return systemCall(WRITE, fd, sSize, (uint64_t) s);
}

uint64_t time(int fd, char * s, int sSize) {
	return systemCall(TIME, fd, 0, 0);
}