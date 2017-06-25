#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include <interruptions.h>

#include <driverVideo.h>
#include <driverMouse.h>
#include <terminal.h>

#define TIMER 100000000


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();
void loading(void);

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

void loading(void) {
	long timer = TIMER;
	while(timer) {
		timer--;
	}
}


int main()
{	
	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();

	ncPrint("[Finished]");

	loading();

	// print black screen
	clearScreen();

	// welcome message
	welcomeMessage();
	clearScreen();

	// set IDT
	// set interruption (IDT) handlers
	// set PIC mask
	initialize_Mouse();
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
	setPicMaster(0xF9);
	// setPicMaster(0x0000);
	setPicSlave(0xEF);
	sti();
	draw_pixel(15,15,0x01);

	terminal();

	while(1);

	// shell();

	return 0;
}
