#include "include/lib.h"
#include "include/systemCalls.h"

int printf(char * s) {
	return write(s);
}

int scanf(void) {
	// systemCall a read
	char buffer[50] = {0};
	read(buffer);
	return 0;
}

void putChar(char c) {
	char s[] = {c, 0};
	printf(s);
}

int getChar(void) {
	// ?
	return 0;
}

int strcmp(char * s1, char * s2) {
	do {
		if(*s1 != *s2) {
			return 0;
		}
	} while(*s1 != '\n' && *s2 != '\n');
	return 1;
}