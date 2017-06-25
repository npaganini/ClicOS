#include "include/systemCalls.h"

uint64_t read(char * s, int sSize) {
	return systemCall(READ, sSize, (uint64_t) s);
}

uint64_t write(char * s) {
	// printOnScreen("Huh");
	return systemCall(WRITE, 0, (uint64_t) s);
}

uint64_t time() {
	return systemCall(TIME, 0, 0);
}
