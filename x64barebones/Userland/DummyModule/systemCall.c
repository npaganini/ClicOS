#include "include/systemCall.h"

uint64_t write(char * s) {
	return systemCall(WRITE, (uint64_t) s, 0);
}