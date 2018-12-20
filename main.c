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

	numpad(6, 17);
	printf("Output from numpad:" CGRN " \"%s\"" CNRM "\n", outstring);	
	//printf("%s =" CGRN " %s\n" CNRM, outstring, expression);

	return 0;
}
