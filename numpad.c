#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define WHITE 15

char outstring[1024];

void spacerem(char source[])
{
	char* i = source;
	char* j = source;
	while(*j != 0)
	{
		*i = *j++;
		if(*i != ' ') i++;
	}
	*i = 0;
}

int numpad(int y, int x)
{
	setlocale(LC_ALL, "");

	char numpad[20][100] = {" 7 ", " 4 ", " 1 ", " 0 ", " 8 ", " 5 ", " 2 ", " . ", " 9 ", " 6 ", " 3 ", " P ", "Del", " * ", " + ", "Ans", " C ", " / ", " - ", " = "};
	int maxx, maxy;
	int focused = 0;
	int last = 0;

	initscr();

	getmaxyx(stdscr, maxy, maxx);
	WINDOW* calscr = newwin(3, x, maxy/2 - 3, maxx/2 - x/2);
	WINDOW* numwin = newwin(y, x, maxy/2, maxx/2 - x/2);
	refresh();
	box(calscr, 0, 0);
	box(numwin, 0, 0);
	wrefresh(numwin);
	wrefresh(calscr);
	keypad(numwin, true);

	while (1 == 1)
	{
		int newx = 1;
		int count = 0;

		for (int i = 0; i < 20; i++)
		{
			if (i == focused)
			{
				wattron(numwin, A_REVERSE);
			} else {
				wattroff(numwin, A_REVERSE);
			}
			if (i == 4 || i == 8 || i == 12 || i == 16 || i == 20)
			{
				newx += 3;
				count = 0;
			}
			mvwprintw(numwin, count + 1, newx, numpad[i]);
			count++;
		}
		int choice = wgetch(numwin);

		switch(choice)
		{
			case KEY_UP:
			{
				last = focused;
				focused--;
				if (focused == -1 || focused == 3 || focused == 7 || focused == 11 || focused == 15)
				{
					focused = last;
				}	
				break;
			}
			case KEY_DOWN:
			{
				last = focused;
				focused++;
				if (focused == 4 || focused == 8 || focused == 12 || focused == 16 || focused == 20)
				{
					focused = last;
				}
				break;
			}
			case KEY_RIGHT:
			{	
				last = focused;
				focused = focused + 4;
				if (focused > 19)
				{
					focused = last;
				}
				break;
			}
			case KEY_LEFT:
			{
				last = focused;
				focused -= 4;
				if (focused < 0)
				{
					focused = last;
				}
				break;
			}
		}
		if (choice == 10)
		{
			if (strcmp(numpad[focused], " = ") == 0)
			{
				break;
			}
			char tmp[1][4] = {" "};
			strcpy(tmp[0], numpad[focused]);
			spacerem(tmp[0]);
			strcat(outstring, tmp[0]);
			mvwprintw(calscr, 1, strlen(outstring), "%s", tmp[0]);
			wrefresh(calscr);
		}
	}
	system("clear");

	endwin();	
	return 0;
}
