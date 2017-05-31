#include <interruptions.h>
#include <driverVideo.h>

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

// static int i = 0;
// char *video = (char *) 0xB8000;
	

void tickHandler() {
	// video[i++] = i;
	// Here would go (jump to the interrupt attention routine) the Scheduler to swap between tasks to run.
}

void keyboardHandler() {
	// printOnScreen("Hola");	Entra aca correctamente 1 vez
	// char c[] = {'a'};
	// c[0] = (char)();
	// printOnScreen(c);		// interruption not working... hay que arreglar el asm? el llamado a esta funcion?
	keyboard_handler();
}

typedef void (*handler_t)(void);

handler_t handlers[] = {tickHandler, keyboardHandler};

void irqDispatcher(int irq) {
	handlers[irq]();
}
