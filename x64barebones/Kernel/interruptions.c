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
	timer--;
}

void keyboardHandler() {
	keyboard_handler();		// in keyboard driver
}

void mouseHandler() {
	mouse_handler();		// in mouse driver
}

void systemCallHandler(int instruction, char * s, int sSize) {
	switch(instruction) {
		case TIME:
			printOnScreen("La hora es: ");
			displayTime();
			break;
		case READ:
			if(sSize == 1) {
				*s = (int) getCharFromBuffer();
			} else {
				cpyFromBuffer(s);
			}
			break;
		case WRITE:
			if(*s == 0) {
				clearScreen();
			} else {
				printOnScreen(s);
			}
			break;
		default:
			break;
	}
}

typedef void (*handler_t)(void);

handler_t handlers[] = {tickHandler, keyboardHandler, mouseHandler};

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
			break;
		default:
			break;
	}
}

void setIDT() {
	iSetHandler(0x20, (uint64_t) irq0Handler);
	iSetHandler(0x21, (uint64_t) irq1Handler);
	iSetHandler(0x22, (uint64_t) irq2Handler);
	iSetHandler(0x23, (uint64_t) irq3Handler);
	iSetHandler(0x24, (uint64_t) irq4Handler);
	iSetHandler(0x25, (uint64_t) irq5Handler);
	iSetHandler(0x26, (uint64_t) irq6Handler);
	iSetHandler(0x27, (uint64_t) irq7Handler);
	iSetHandler(0x28, (uint64_t) irq8Handler);
	iSetHandler(0x29, (uint64_t) irq9Handler);
	iSetHandler(0x2A, (uint64_t) irq10Handler);
	iSetHandler(0x2B, (uint64_t) irq11Handler);
	iSetHandler(0x2C, (uint64_t) irq12Handler);
	iSetHandler(0x2D, (uint64_t) irq13Handler);
	iSetHandler(0x2E, (uint64_t) irq14Handler);
	iSetHandler(0x2F, (uint64_t) irq15Handler);
	iSetHandler(0x80, (uint64_t) irq80Handler);
}