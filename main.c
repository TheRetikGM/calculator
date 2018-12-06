#include <ncurses.h>
#include <stdlib.h>
#include "numpad.h"

int main()
{
	numpad(6, 17);
	printf("napsal jsi: %s\n", outstring);
	return 0;
}
