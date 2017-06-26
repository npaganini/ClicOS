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

void map_page(void * physicalAddress, void * virtualAddress)
{
    // Make sure that both addresses are page-aligned.
	unsigned long PDIndex = (unsigned long)virtualAddress >> 21 & 0x01FF;

    unsigned long * PD = ((unsigned long *) 0x10000) + (8 * PDIndex);
    // PD[PDIndex] = ((unsigned long)physicalAddress) & 0x08F; // Flags
    *PD = ((unsigned long)physicalAddress) & 0x08F; // Flags


    // unsigned long PDIndex = (unsigned long)virtualAddress >> 21 & 0x1FF;
    // char * PDIndexStr = longToChar(PDIndex);
    // printOnScreen("PDIndex");
    // printOnScreen(PDIndexStr);
    // unsigned long Index = (unsigned long) virtualAddress & 0x1FFFFF;
    // char * IndexStr = longToChar(Index);
    // printOnScreen("Index");
    // printOnScreen(IndexStr);
    // unsigned long * PD = ((unsigned long *) 0x10000) + (/*0x200000*/ 0x8 * PDIndex);
    // char * PDStr = (char *) PD;
    // printOnScreen(PDStr);

//    PD[Index] = ((unsigned long)physicalAddress) & 0x8F; //flags
    // *PD = ((unsigned long)physicalAddress - Index) & 0x8F; //flags
 
    // unsigned long PDIndex = (unsigned long)virtualAddress >> 21 & 0x1FF;
    // // char * PDIndexStr = intToChar(PDIndex);
    // // printOnScreen(PDIndexStr);
    // unsigned long Index = (unsigned long) virtualAddress & 0x1FFFFF;
    // unsigned long * PD = ((unsigned long *) 0x10000); //+ (0x200000 * PDIndex);


    // PD[PDIndex] = (((unsigned long)physicalAddress + Index) & 0x08F); //flags

    // unsigned long * pd = (unsigned long *)0xFFFFF000;
    // // Here you need to check whether the PD entry is present.
    // // When it is not present, you need to create a new empty PT and
    // // adjust the PDE accordingly.
 
    // unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // // Here you need to check whether the PT entry is present.
    // // When it is, then there is already a mapping present. What do you do now?
 
    // pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; // Present
 
    // // Now you need to flush the entry in the TLB
    // // or you might not notice the change.
}

// void change(void* dir1, void* dir2) {
void change(void) {
	// char* vidStart = (char *) 0xB8000;
    char* hola = (char *) 0xA00000;
    *(hola) = 'c';
    char* hola2 = (char *) 0xB00000;
    *(hola2) = 'a';
    map_page(hola, hola);
    map_page(hola2, hola2);
    printOnScreen(hola);
    printOnScreen(hola2);
    map_page(hola, hola2);
    // map_page(hola2, hola2);
    printOnScreen(hola);
    printOnScreen(hola2);
}

int main()
{
	/*/
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
	/**/

	// memcpy(userland, sampleCodeModuleAddress, 0x200000);

	EntryPoint sampleCodeModule = (EntryPoint) sampleCodeModuleAddress;
	// EntryPoint userGuest = (EntryPoint) sampleCodeModuleAddress;

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
	setIDT();
	setPicMaster(0xF9);
	// setPicMaster(0x0000);
	setPicSlave(0xEF);
	sti();

	// change();

	// terminal();

	// int mhm = 0;
	// mhm = sampleCodeModule();
	sampleCodeModule();

	// if(!mhm) {
	// 	printOnScreen("llega a printf");
	// }

	while(1);

	return 0;
}
