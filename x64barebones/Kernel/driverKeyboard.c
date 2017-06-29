#include <interruptions.h>
#include <driverVideo.h>
#include <driverKeyboard.h>


static char KEYS_MAPPING[] = {0, 'ESC', '1', '2', '3', '4', '5', '6', '7', '8', '9', 			// 0 - 10
									'0', '\'', '¿', 'BACKSPACE', 'TAB', 'q', 'w', 'e', 'r', 't',// 11 - 20
								  	'y', 'u', 'i', 'o', 'p', '´', '+', '\n', 'MAYUS', 'a',		// 21 - 30
									's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, '{', 			// 31 - 40
								  	'|', 'LSHIFT', '}', 'z', 'x', 'c', 'v', 'b', 'n', 'm',  	// 41 - 50
								  	',', '.', '-', 0, '*', 0, ' ', 0, 0, 0};					// 51 - 60										// 55 - 62

static char SHIFT_KEYS_MAPPING[] = {0, 'ESC', '!', '\0', '#', '$', '%', '&', '/', '(', ')', 	// 0 - 10
									'=', '?', '¡', 0, 'TAB', 'Q', 'W', 'E', 'R', 'T',			// 11 - 20
								  	'Y', 'U', 'I', 'O', 'P', '¨', '*', '\n', 'MAYUS', 'A',		// 21 - 30
									'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 0, '[', 			// 31 - 40
								  	'°', 'LSHIFT', ']', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',  	// 41 - 50
								  	';', ':', '_', 0, '*', 0, ' ', 0, 0, 0};					// 51 - 60

static int mayus = 0;
static int bufferPlace = 0;
static char buffer[ROWS*COLS] = {0};
// buffer[bufferPlace] = 28;
// bufferPlace++;

void keyboard_handler(void) {
	int keycode;

	keycode = read_port(0x60);

	buffer[bufferPlace] = keycode;

	if(keycode >= 0 &&  keycode < MAX_KEYPRESSED) {
		if(keycode == 14) {
			if(buffer[bufferPlace-1] == 28) {
				backspace(1);
			}
			backspace(0);
			if(bufferPlace == 0) {
				bufferPlace = ROWS * COLS - 1;
			} else {
				bufferPlace--;
			}
		} else {
			switch(keycode) {
				case 15:
					printOnScreen("    ");
					break;
				case 28:
					myNewLine();
					break;
				case 29:
				case 42:
					if(mayus) {
						mayus = 0;
					} else {
						mayus = 1;
					}
					break;
				default:
					if(mayus) {
						printOnScreenChar(SHIFT_KEYS_MAPPING[keycode]);
					} else {
						printOnScreenChar(KEYS_MAPPING[keycode]);
					}
					break;
			}
			if(bufferPlace == (ROWS * COLS - 1)) {
				bufferPlace = 0;
			} else {
				bufferPlace++;
			}
		}
	}
}

char auxCopy[50] = {0};

// void cpyToBuffer(char * s) {
// 	int i = 0;
// 	do {
// 			auxCopy[i] = SHIFT_KEYS_MAPPING[buffer[bufferPlace - i]];
// 		i++;
// 		if(i > 49) {
// 			return;
// 		}
// 	} while(buffer[bufferPlace - i] != 28);
// 	*(s+i+1) = 0;
// 	while(*(s+i) != '\n') {
// 		*(s+i) = auxCopy[i];
// 		i--;
// 		if(i < 0) {
// 			return;
// 		}
// 	}
// }

void cpyFromBuffer(char * s) {
	int i = 0;
	int j = 0;
	printOnScreen("Arranca el copy ");
	do {
		auxCopy[i] = SHIFT_KEYS_MAPPING[buffer[bufferPlace - i]];
		i++;
		// if(i > 49) {
		// 	return;
		// }
	} while(buffer[bufferPlace - i] != 28);
	i--;
	while(i > 0) {
		*(s+j) = auxCopy[i];
		i--;
		j++;
	}
	printOnScreen("Hace el copy ");
	*(s+j) = 0;
	for(i = 0; i < 50; i++) {
		auxCopy[i] = 0;
	}
	printOnScreen("Termina el copy ");
}
