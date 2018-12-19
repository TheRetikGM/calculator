#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "numpad.h"
#define CGRN  "\x1B[32m"
#define CNRM  "\x1B[0m"

int main()
{
	setlocale(LC_ALL, "");
	char buf[1024];

	numpad(6, 17);
	printf("Output from numpad:" CGRN " \"%s\"" CNRM "\n", outstring);
	sprintf(buf, "echo %s | ./dscc", outstring);
	system(buf);
	return 0;
}
