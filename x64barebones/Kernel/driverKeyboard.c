#include <interruptions.h>
#include <driverVideo.h>
#include <driverKeyboard.h>


static char KEYS_MAPPING[] = {0, 'ESC', '1', '2', '3', '4', '5', '6', '7', '8', '9', 			// 0 - 10
									'0', '\'', '¿', 0, '    ', 'q', 'w', 'e', 'r', 't',// 11 - 20
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

void keyboard_init(void) {
	write_port(0x21, 0xFD);
}

void keyboard_handler(void) {
	// unsigned char status;
	char keycode;



	// // write End of Interrupt
	// write_port(0x20, 0x20);

	// status = read_port(0x64);	// polling?
	keycode = read_port(0x60);
	if(keycode < 0) {
		return;
	}
	if(keycode == 28) {
		myNewLine();
	}
	if(keycode == 17) {
		printOnScreen("Pepito");
	}
	// if(keycode == SHIFT)
	printOnScreenChar(KEYS_MAPPING[keycode]);
}
