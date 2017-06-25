#include <driverVideo.h>

char* vidStart = (char *) 0xB8000;

static int pointer = 0;

char ans[MAX_INT] = {0};

void printOnScreenChar(char c) {
	if(pointer == 2*ROWS*COLS) {
		scroll();
	}
	*(vidStart + pointer) = c;
	*(vidStart + pointer + 1) = 0x07;
	pointer += 2;
}

void printOnScreen(char* string) {
	int i = 0;
	while(string[i] != 0) {
		if(pointer == 2*ROWS*COLS) {
			scroll();
		}
		*(vidStart + pointer) = string[i];
		*(vidStart + pointer + 1) = 0x07;
		pointer += 2;
		i++;
	}
}

void draw_pixel(int x, int y, int color){
	int position= x*1 + y*80;
	*(vidStart + position) = 'm';
	*(vidStart + position + 1) = 0x07;
}

void clearScreen() {
	for(pointer = 0; pointer < (ROWS*COLS*2); pointer += 2) {
		*(pointer+vidStart) = ' ';
		*(pointer+vidStart+1) = 0x00;
	}
	pointer = 0;
}

void myNewLine() {
	if(pointer >= 2*ROWS*COLS && pointer <= 2*(ROWS-1)*COLS) {
		scroll();
	}
	pointer = ((pointer / (COLS * 2)) + 1) * COLS * 2;
}

char* intToChar(int n) {
	int i;
	char aux[MAX_INT] = {0};
	for(i = 0; i < 2; i++) {
		aux[i] = (n % 10) + '0';
		n /= 10;
	}
	for(i = 0; i < 2; i++)
		ans[i] = aux[1-i];
	return ans;
}

char* longToChar(unsigned long n) {
	unsigned long i;
	char aux[MAX_LONG] = {0};
	for(i = 0; i < 2; i++) {
		aux[i] = (n % 10) + '0';
		n /= 10;
	}
	for(i = 0; i < 2; i++)
		ans[i] = aux[1-i];
	return ans;
}

void displayTime() {
	// BCD where 57 means [0101|0111] which is 87
	// int secs = 0;
	// int secsBCD;
	int mins = 0;
	int minsBCD;
	int hours = 0;
	int hoursBCD;
	// secsBCD = (int)_sysTime(0);
	minsBCD = (int)_sysTime(2);
	hoursBCD = (int)_sysTime(4);
	mins += (minsBCD & 0xF);
	mins += ((minsBCD & 0xF0)>>4)*10;
	hours += (hoursBCD & 0xF);
	hours += ((hoursBCD & 0xF0)>>4)*10;
	switch(hours) {
		case 0: {
			hours = 24;
			break;
		}
		case 1: {
			hours = 25;
			break;
		}
		case 2: {
			hours = 26;
			break;
		}
	}
	hours -= GMT;
	printOnScreen(intToChar(hours));
	printOnScreen(":");
	printOnScreen(intToChar(mins));
}

void displayDate() {
	int day = 0;
	int dayBCD = (int) _sysTime(7);
	day += (dayBCD & 0xF);
	day += ((dayBCD & 0xF0)>>4)*10;
	int month = 0;
	int monthBCD = (int) _sysTime(8);
	month += (monthBCD & 0xF);
	month += ((monthBCD & 0xF0)>>4)*10;
	printOnScreen(intToChar(day));
	printOnScreen("/");
	printOnScreen(intToChar(month));
	// int week;
	// int month;
	// int year;
}

void welcomeMessage() {
	long timer = TIMER;
	pointer += (ROWS*COLS-CENTERED);
	printOnScreen("Welcome to ClicOS!");

	myNewLine();

	myNewLine();
	pointer += CENTERED*2.5+4;
	printOnScreen(" Today's date is: ");
	displayDate();

	myNewLine();
	pointer += CENTERED*2.5+4;
	printOnScreen("   The time is: ");
	displayTime();

	while(timer) {
		timer--;
	}
}

void backspace(int newline) {
	if(pointer > 0) {
		switch(newline) {
			case 0:
				pointer -= 2;
				printOnScreen(" ");
				pointer -= 2;
				break;
			case 1:
				do {
					pointer -= 4;
				} while((pointer > 0) && (*(vidStart + pointer) == ' '));
				pointer += 6;
				break;
			default:
				break;
		}
	}
}

void scroll(void) {
	int ipointer, jpointer;
	int end = (ROWS-1)*COLS*2;
	for(ipointer = 0, jpointer = COLS*2; ipointer < end; ipointer++, jpointer+=2) {
		*(vidStart + ipointer) = *(vidStart + jpointer);
		ipointer++;
		*(vidStart + ipointer) = 0x07;
	}
	for(ipointer = end; ipointer < (ROWS*COLS*2); ipointer += 2) {
		*(ipointer + vidStart) = ' ';
		*(ipointer + vidStart + 1) = 0x00;
	}
	pointer = end;
}