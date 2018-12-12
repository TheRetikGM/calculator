#include <ncurses.h>
#include <stdlib.h>
#include "numpad.h"
#define CGRN  "\x1B[32m"
#define CNRM  "\x1B[0m"

int main()
{
	char buf[1024];

	numpad(6, 17);
	printf("Output from numpad: %s\"%s\"%s\n", CGRN, outstring, CNRM);
	sprintf(buf, "echo %s | ./dscc", outstring);
	system(buf);
	return 0;
}
