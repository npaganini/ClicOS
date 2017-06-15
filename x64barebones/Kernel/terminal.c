#include <terminal.h>
#include <driverVideo.h>

void terminal(void) {
	int exit = 0;
	do {
		printOnScreen("[User]$ ");
		while(1);
	} while(!exit);
	return !exit;
}