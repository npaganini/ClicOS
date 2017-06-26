#include <terminal.h>
#include <driverVideo.h>

void terminal(void) {
	// pick user / samplecodemodule
	displayWelcomeMsg();
	// EntryPoint sampleCodeModule = (EntryPoint) sampleCodeModuleAddress;
	// EntryPoint userGuest = (EntryPoint) sampleCodeModuleAddress;
}

void displayWelcomeMsg(void) {
	printOnScreen("Please select the module to run:");
}