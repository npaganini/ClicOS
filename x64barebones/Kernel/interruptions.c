#include <interruptions.h>
#include <driverVideo.h>
#include <driverKeyboard.h>

#pragma pack(push)
#pragma pack(1)

typedef struct { 
	uint16_t offset_l; //bit 0..15
	uint16_t selector;
	uint8_t zero_l;
	uint8_t attrs;
	uint16_t offset_m; //16..31
	uint32_t offset_h; //32..63
	uint32_t zero_h;
} IDTEntry_t;

#pragma pack(pop)

static IDTEntry_t* IDT = (IDTEntry_t*) 0x0;

void iSetHandler(int index, uint64_t handler) {
	IDT[index].offset_l = (uint16_t) handler & 0xFFFF;
	IDT[index].offset_m = (uint16_t) (handler >> 16) & 0xFFFF;
	IDT[index].offset_h = (uint32_t) (handler >> 32) & 0xFFFFFFFF;
	
	IDT[index].selector = 0x08;
	IDT[index].zero_l = 0;
	
	IDT[index].attrs = 0x8E;
	IDT[index].zero_h = 0;	
}

void tickHandler() {
	// Here would go (jump to the interrupt attention routine) the Scheduler to swap between tasks to run. Not part of this project.
}

void keyboardHandler() {
	keyboard_handler();		// in keyboard driver
}

void mouseHandler() {
	mouse_handler();
}

void systemCallHandler(int instruction, char * s, int sSize) {
	// acá debería identificar que quiere hacer y decirle a quien mandarle
	// el write imprime en pantalla y le pasa lo escrito al buffer
	switch(instruction) {
		case TIME:
			displayTime();
			break;
		case READ:
			// read con strcpy del buffer de driverKeyboard
			// return lo que te da el strcpy
			break;
		case WRITE:
			printOnScreen("Funciona!");
			printOnScreen(s);
			break;
		default:
			break;
	}
}

typedef void (*handler_t)(void);

handler_t handlers[] = {tickHandler, keyboardHandler, mouseHandler, systemCallHandler};

void irqDispatcher(int irq) {
	switch(irq) {
		case 0:
			handlers[0]();
			break;
		case 1:
			handlers[1]();
			break;
		case 12:
			handlers[2]();
			break;
		case 16:
			handlers[3]();
			break;
		default:
			printOnScreen("Nope");
			break;
	}
}