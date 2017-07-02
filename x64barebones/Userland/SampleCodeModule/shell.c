#include "include/shell.h"
#include "include/lib.h"

static char buffer[50] = {0};

int shell(void) {
	int exit = 0;
	// int pepito = 0;
	// pepito = printf("hola\n");
	while(!exit) {
		printf("[SCM]$ ");
		getInput();
		// printf(buffer);		// NO IMPRIME NADA. NO ESTA COPIANDO BIEN?
		while(buffer[0] != '\n');
		exit = processCommand();
	}
	return exit;
	// return pepito;
}

void getInput(void) {
	// printf("2\n");							// TODO: TRACE STEPS TO SEE IF THIS WORKS PROPERLY
	scanf(buffer);
}

int processCommand(void) {
	// maquina de estados o varios strcmp
	if(strcmp(buffer, "help")) {
		helpMenu();
	} else if(strcmp(buffer, "null")) {
		clear();
	} else if(strcmp(buffer, "time")) {
		showCurrTime();
	} else if(strcmp(buffer, "exit")) {
		return 1;
	// } else if(echo((char *) strcmp(buffer, "echo"))) {
	} else {
		int i;
		char aux[4];
		for(i = 0; i < 4; i++) {
			aux[i] = buffer[i];
		}
		if(strcmp(aux, "echo")) {
			echo(buffer+5);
		} else {
			printf("Comando no reconocido.");
		}
	}
	return 1;
}

void helpMenu(void) {
	printf("Los comandos reconocidos son:\n");
	printf("null:              Limpia la pantalla.\n");
	printf("echo [mensaje]:    Muestra el mensaje.\n");
	printf("time:              Muestra la hora actual.\n");
	printf("help:              Muestra este menu de ayuda.\n");
}

void clear(void) {
	char null[1] = {0};
	printf(null);
}

void showCurrTime(void) {
	showTime();
}

void echo(char * s) {
	printf(s);
}
