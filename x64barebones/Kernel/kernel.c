#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>

#include <interruptions.h>

#include <driverVideo.h>
#include <driverMouse.h>
#include <driverKeyboard.h>
#include <terminal.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const dummyModuleAddress = (void*)0x600000;

typedef int (*EntryPoint)();

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
		sampleDataModuleAddress,
		dummyModuleAddress
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

uint64_t *PD = (uint64_t *) 0x10000; 
int PDIndex = 2;

void map_page(uint64_t physicalAddress)
{
    //Si yo quisiera poner esta pagina presente....
 //	PD[PDIndex] |= 0x1;
	uint64_t mask = 0xFFF00000001FFFFF;
	uint64_t aux = PD[PDIndex] & mask;
	PD[PDIndex] =  aux | (physicalAddress & ~0x1FFFFF);
	//reescribir el cr3 	
	// mov rax, cr3 ; mov cr3, rax
	rewrite_CR3();
}
// map_page(0x800000);


// void change(void* dir1, void* dir2) {
// void change(void) {
// 	// char* vidStart = (char *) 0xB8000;
//     char* hola = (char *) 0xA00000;
//     *(hola) = 'c';
//     char* hola2 = (char *) 0xB00000;
//     *(hola2) = 'a';
//     map_page(hola, hola);
//     map_page(hola2, hola2);
//     printOnScreen(hola);
//     printOnScreen(hola2);
//     map_page(hola, hola2);
//     // map_page(hola2, hola2);
//     printOnScreen(hola);
//     printOnScreen(hola2);
// }

void displayModuleMsg(void) {
	printOnScreen("Please select the module to run:\n");
	printOnScreen("1: Sample Code Module\n");
	printOnScreen("2: Dummy Module\n");
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
	*/

	int option = 0;

	// memcpy(userland, sampleCodeModuleAddress, 0x200000);

	EntryPoint sampleCodeModule = (EntryPoint) sampleCodeModuleAddress;
	EntryPoint dummyModule = (EntryPoint) dummyModuleAddress;

	loading();

	// print black screen
	clearScreen();

	// welcome message
	welcomeMessage();

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
		clearScreen();
	do {
		// char aux[2] = {0};
		displayModuleMsg();
		while(getCharFromBuffer() != '\n');
		option = getOption() - '0';
		clearBuffer();
		switch(option) {
			case 1:
				clearScreen();
				// map_page(sampleCodeModuleAddress);
				option = sampleCodeModule();
				break;
			case 2:
				clearScreen();
				map_page(dummyModuleAddress);
				option = dummyModule();
				break;
			default:
				printOnScreen("Not a module\n");
				break;
		}
	} while(1);

	return 0;
}
