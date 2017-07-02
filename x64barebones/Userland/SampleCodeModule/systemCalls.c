#include "include/systemCalls.h"

uint64_t read(char * s, int sSize) {
	return systemCall(READ, (uint64_t) s, sSize);
}

uint64_t write(char * s) {
	return systemCall(WRITE, (uint64_t) s, 0);
}

uint64_t time() {
	return systemCall(TIME, 0, 0);
}
