#include "include/systemCall.h"

void dummyPrintf(char * s) {
	write(s);
}

int main() {
	dummyPrintf("Ha! I'm a dummy, you dummy!\n");
	return 0;
}
