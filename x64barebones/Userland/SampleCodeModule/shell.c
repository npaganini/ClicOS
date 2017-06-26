#include "include/shell.h"
#include "include/lib.h"

int shell(void) {
	int exit = 0;
	// int pepito = 0;
	// pepito = printf("hola\n");
	while(!exit) {
		printf("[SCM]$ ");
		printf("Still good");
		getInput();
		exit = processCommand();
	}
	return !exit;
	// return pepito;
}

void getInput(void) {
	printf("2\n");							// TODO: TRACE STEPS TO SEE IF THIS WORKS PROPERLY
	// read()
	// implements scanf
}

int processCommand(void) {
	// implements strcmp
	return 0;
}

void helpMenu(void) {
	printf("Los comandos reconocidos son:\n");
	printf("clear:             Limpia la pantalla.\n");
	printf("echo [mensaje]:    Muestra el mensaje.\n");
	printf("time:              Muestra la hora actual.\n");
	printf("help:              Muestra este menu de ayuda.\n");
}
