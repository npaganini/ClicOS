#include "include/shell.h"
#include "include/lib.h"

#include <stdio.h>

int shell(void) {
	int exit = 0;
	printf("1\n");
	getInput();
	exit = processCommand();
	return !exit;
}

void getInput(void) {
	printf("2\n");							// TODO: TRACE STEPS TO SEE IF THIS WORKS PROPERLY
	// read()
	// implements scanf
}

void processCommand(void) {
	// implements strcmp
}

void helpMenu(void) {
	printf("Los comandos reconocidos son\n");
	printf("clear:             Limpia la pantalla.\n");
	printf("echo [mensaje]:    Muestra el mensaje.\n");
	printf("time:              Muestra la hora actual.\n");
	printf("help:              Muestra este menu de ayuda.\n");
}