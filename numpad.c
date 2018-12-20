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
	char numpad[20][100] = {" 7 ", " 4 ", " 1 ", " 0 ", " 8 ", " 5 ", " 2 ", " . ", " 9 ", " 6 ", " 3 ", " \u03C0 ", "Del", " * ", " + ", "Ans", " C ", " / ", " - ", " = "};
	char operators[5][8] = {"+", "-", "*", "/", "."};
	int maxx, maxy;
	int focused = 0;
	int last = 0;
	bool lastoperation = true;
	char lastchar[5];
	int picount = 0;

	initscr();

	getmaxyx(stdscr, maxy, maxx);
	WINDOW* calscr = newwin(4, x, maxy/2 - 4, maxx/2 - x/2);
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

		if (choice == 10) 	// if you hit enter
		{
			char tmp[1][4];
			strcpy(tmp[0], numpad[focused]);
			spacerem(tmp[0]);

			if (strcmp(tmp[0], "=") == 0)
			{	
				wclear(calscr);
				box(calscr, 0, 0);
				char buf[1024];
				char buf1[10];
				char expression[1024];
				FILE *file;
				int calmaxx = getmaxx(calscr);

				if (strlen(outstring) != 0)
				{
					sprintf(buf, "echo \"scale=4;%s\" | bc -l", outstring);
					file = popen(buf, "r");
					fscanf(file, " %s", expression);
					wclear(calscr);
					box(calscr, 0, 0);
					mvwprintw(calscr, 1, 1, "%s=", outstring);				
					int i = strlen(expression) - 5;
					strncpy(buf1, expression + i, 5);
					if (strcmp(buf1, ".0000") == 0)
					{
						expression[i] = '\0';
						printw("%s", expression);
						refresh();
					}
					mvwprintw(calscr, 2, calmaxx - strlen(expression) - 1, "%s", expression);
					wrefresh(calscr);
					outstring[0] = '\0';
				}
				else
				{
					mvwprintw(calscr, 1, 1, "0=");
					mvwprintw(calscr, 2, calmaxx - 2, "0");	
					wrefresh(calscr);
				}
			}
			else
			{
				if (strcmp(tmp[0], "C") == 0)
				{
					wclear(calscr);
					wmove(calscr, 1, 1);
					box(calscr, 0, 0);
					wrefresh(calscr);
					outstring[0] = '\0';
					lastoperation = true;
				}
				else if (strcmp(tmp[0], "Del") == 0)
				{
					if (strlen(outstring) > 0)
					{
						outstring[strlen(outstring) - 1] = '\0';
						wclear(calscr);
						box(calscr,0 , 0);
						mvwprintw(calscr, 1, 1, "%s", outstring);	
						wrefresh(calscr);
						if (lastoperation == true) lastoperation = false; 
						else if (strlen(outstring) == 0) lastoperation = true;
					}
				}
				else
				{
					if (lastoperation == true)
					{
						int a = 0;
						for (int i = 0; i < 5; i++)
						{
							if (strcmp(tmp[0], operators[i]) == 0) a++;
						}
						if(a == 0) lastoperation = false;
					}
					if (lastoperation == false)
					{
						int a = 0;
						if (strcmp(tmp[0], "\u03c0") == 0) strcat(outstring, "(4*a(1))");
						else strcat(outstring, tmp[0]);
						wclear(calscr);
						box(calscr, 0, 0);
						mvwprintw(calscr, 1, 1, "%s", outstring);
	
						for (int i = 0; i < 5; i++)
						{
							if (strcmp(tmp[0], operators[i]) == 0) a++;
						}
						if (a == 1) lastoperation = true;
					} 
				}
				strcpy(lastchar, tmp[0]);
				wrefresh(calscr);
			}
		}
	}

	endwin();	
	return 0;
}
