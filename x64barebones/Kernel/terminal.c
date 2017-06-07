#include <terminal.h>
#include <driverVideo.h>

int terminal(void) {
	int exit = 0;
	do {
		printOnScreen("[User]$ ");
		// stuff
		exit = !exit;
	} while(!exit);
	return !exit;
}