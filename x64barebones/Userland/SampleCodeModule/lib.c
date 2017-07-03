#include "include/lib.h"
#include "include/systemCalls.h"

int printf(char * s) {
	return write(s);
}

int scanf(char * s) {
	read(s, 0);
	// *(s+0) = 'h';
	// *(s+1) = 'e';
	// *(s+2) = 'l';
	// *(s+3) = 'p';
	return 0;
}

void putChar(char c) {
	char s[] = {c, 0};
	printf(s);
}

int getChar(void) {
	char c;
	read(&c, 1);
	return (int) c;
}

int strcmp(char * s1, char * s2) {
	int i = 0;
	do {
		if(*(s1+i) != *(s2+i)) {
			return 0;
		}
		i++;
	} while(i < 4);
	if(*(s1+i) == ' ') {
		return (int) *(s1+i+1);
	}
	return 1;
}

void showTime(void) {
	time();
	printf("\n");
}