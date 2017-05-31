#include <interruptions.h>
#include <driverVideo.h>
#include <driverKeyboard.h>


static char KEYS_MAPPING[] = {0, 'ESC', '1', '2', '3', '4', '5', '6', '7', '8', '9', 			// 0 - 10
									'0', '\'', '¿', 'BACKSPACE', '    ', 'q', 'w', 'e', 'r', 't',// 11 - 20
								  	'y', 'u', 'i', 'o', 'p', '´', '+', '\n', 0, 'a',			// 21 - 30
									's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, '{', 			// 31 - 40
								  	'|', 'SHIFT', '}', 'z', 'x', 'c', 'v', 'b', 'n', 'm',  		// 41 - 50
								  	',', '.', '-', 0, '*', 0, ' ', 0, 0, 0};				// 51 - 60										// 55 - 62

static char SHIFT_KEYS_MAPPING[] = {0, 'ESC', '!', '\0', '#', '$', '%', '&', '/', '(', ')', 	// 0 - 10
									'=', '?', '¡', 0, '    ', 'Q', 'W', 'E', 'R', 'T',// 11 - 20
								  	'Y', 'U', 'I', 'O', 'P', '¨', '*', '\n', 0, 'A',			// 21 - 30
									'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 0, '[', 			// 31 - 40
								  	'°', 'SHIFT', ']', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',  		// 41 - 50
								  	';', ':', '_', 0, '*', 0, ' ', 0, 0, 0};				// 51 - 60

static int shift = 0;

void keyboard_handler(void) {
	// unsigned char status;
	char keycode;

	// printOnScreen("Pepit");		// working correctly
	// printOnScreenChar('o');		// working correctly


	keycode = read_port(0x60);

	printOnScreenChar(keycode);
	// if(keycode < 0) {
	// 	return;
	// }
	switch(keycode) {
		case 28: {
			myNewLine();
			break;
		}
		case 14: {
			backspace();
			break;
		}
		// case 42: {
		// 	shift = 1;
		// }
		default: {
			if(shift) {
				printOnScreenChar(SHIFT_KEYS_MAPPING[keycode]);
			} else {
				printOnScreenChar(KEYS_MAPPING[keycode]);
			}
			break;
		}
	}
}
