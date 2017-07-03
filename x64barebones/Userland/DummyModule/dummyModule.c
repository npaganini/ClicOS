#include "include/systemCall.h"

void dummyPrintf(char * s) {
	write(s);
}

int main() {
	dummyPrintf("I'm a dummy!\n");
	return 0;
}
