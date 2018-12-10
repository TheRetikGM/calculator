#include <ncurses.h>
#include <stdlib.h>
#include "numpad.h"

int main()
{
	char buf[1024];

	numpad(6, 17);
	printf("Output from numpad: \"%s\"\n", outstring);
	sprintf(buf, "echo %s | ./dscc", outstring);
	system(buf);
	return 0;
}
