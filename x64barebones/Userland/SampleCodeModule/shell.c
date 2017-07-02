#include "include/shell.h"
#include "include/lib.h"

static char buffer[50] = {0};

int shell(void) {
	int exit = 0;
	while(!exit) {
		printf("[SCM]$ ");
		while(getChar() != '\n');
		getInput();
		// printf(buffer);
		exit = processCommand();
		clearShellBuffer();
		if(exit) {
			printf("Cerrando modulo.\n");
		}
	}
	return exit;
}

void getInput(void) {
	scanf(buffer);
}

int processCommand(void) {
	// maquina de estados o varios strcmp
	// printf(buffer);
	if(strcmp(buffer, "help")) {
		helpMenu();
		// printf("HELP\n");
		return 0;
	} else if(strcmp(buffer, "null")) {
		clear();
		// printf("CLEAR\n");
		return 0;
	} else if(strcmp(buffer, "time")) {
		// printf("TIME\n");
		showCurrTime();
		return 0;
	} else if(strcmp(buffer, "exit")) {
		// printf("EXIT\n");
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
	return 0;
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

void clearShellBuffer(void) {
	int i;
	for(i = 0; i < 50; i++) {
		buffer[i] = 0;
	}
}