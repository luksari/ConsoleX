#include "rogue.h"

int screenSetup()
{
	initscr();
	curs_set(0);
	resize_term(MAX_HEIGHT, MAX_WIDTH);
	system( "chcp 852" );
	start_color();
	noecho();
	refresh();
	srand(time(NULL));
	return 1;
}
int printGameHub(Level * level)
{
	printTextBox("You are in empty wet dungeon");
	mvprintw(28, 0, "    Level: %d", level->round);
	printw("    Gold: %d", level->user->gold);
	printw("    HP: %d/%d", level->user->health, level->user->maxHealth);
	printw("    Exp: %d", level->user->experience);
	printw("    Attack: %d", level->user->attack);

	return 1;
}
int printTextBox(char *ch)
{
	WINDOW * win;
	win = newwin(3, 43, 27, 61);
	box(win, 0, 0);
	mvwprintw(win, 1, 1, "%s", ch);
	wrefresh(win);
	return 1;
}
int betweenLevel(Level * level)
{
		clear();
		refresh();
		char ch;
		WINDOW *win;
		printLogo(stdscr);
		win = newwin(3, 20, (MAX_HEIGHT / 2) - 3, (MAX_WIDTH / 2) - 8);
		keypad(win, TRUE);
		box(win, 0, 0);
		mvwprintw(win, 1, 4, "Next Level %d", (int)(level->round)+1);
		wrefresh(win);
		if (ch = getch())
		{
			endLevel(level);
		}
		return 1;
}
int endGame(Level * level)
{
	clear();
	refresh();
	char ch;
	while (1)
	{
		printLogo(stdscr);
		mvprintw(10, 20, "You've scored %d points", level->user->experience);
		mvprintw(11, 20, "You've acquired %d gold", level->user->gold);
		if (level->round < 6)
		{
			mvprintw(12, 20, "You've died on level %d", level->round);
		}
		else
			mvprintw(12, 20, "You've defeated dungeon, You are the best warrior in Ascirnia");
		mvprintw(20, 40, "Press, [q] to quit");
		if (ch = getch() == 'q')
		{
			clear();
			break;
		}
	}
	return 0;
}

int menuLoop()
{
	refresh();

	WINDOW *w;

	char list[3][10] = { "New Game", "Lore", "Exit" };
	char item[10];
	int ch, i = 0, width = 12;

	w = newwin(8, 12, (MAX_HEIGHT / 2) - 3, (MAX_WIDTH / 2) - 8);
	box(w, 0, 0);

	for (i = 0; i<3; i++) 
	{
		if (i == 0)
			wattron(w, A_REVERSE);
		else
			wattroff(w, A_REVERSE);
		sprintf(item, "%-7s", list[i]);
		mvwprintw(w, i + 1, 2, "%s", item);
	}

	printLogo(stdscr);

	wrefresh(stdscr);
	wrefresh(w);

	i = 0;
	keypad(w, TRUE); 

	while ((ch = wgetch(w)) != 'q') 
	{
		sprintf(item, "%-7s", list[i]);
		mvwprintw(w, i + 1, 2, "%s", item);
		switch (ch)
		{
		case KEY_UP:
			i--;
			i = (i<0) ? 2 : i;
			break;
		case KEY_DOWN:
			i++;
			i = (i>2) ? 0 : i;
			break;
		case 10:
			switch (i)
			{
			case 0:
				gameLoop(1);
				return 1;
			case 1:
				helpLoop();
				return 2;
			case 2:
				return 0;
				break;
			}
			
		}
		wattron(w, A_REVERSE);
		sprintf(item, "%-7s", list[i]);
		mvwprintw(w, i + 1, 2, "%s", item);
		wattroff(w, A_REVERSE);
	}
	clear();
	delwin(w);
	endwin();
	return 1;
}
int helpLoop()
{
	refresh();
	char ch;

	while (1)
	{
		printLogo(stdscr);
		mvprintw(10, 1, "Welcome in unfriendly world of Ascirnia, there is a lot of creatures which can be serious danger");
		mvprintw(11, 1, "To move, use WASD keys, W - up, A - left, S - down, D - right");
		mvprintw(12, 1, "Your character is symboled by @, Enemies are D, X, G, T");
		mvprintw(13, 1, "You can walk on %c, %c, %c", FLOOR, ROAD, DOOR);
		mvprintw(14, 1, "You can't walk on %c, %c, %c and empty space", SIDEWALL, TOPWALL, BOTWALL);
		mvprintw(15, 1, "Items you can get are symboled by %c, %c, %c, and %c", ATK_BOOSTER, HP_BOOSTER, HP_POTION, GOLD);
		mvprintw(16, 1, "Dungeon contains 6 levels with different enemies, slain them to get points");
		mvprintw(17, 1, "Level ends when you defeat all monsters and get all items");
		mvprintw(20, 40, "Press, [q] to quit");
		ch = getch();
		if (ch == 'q')
		{
			clear();
			menuLoop();
			return 0;
		}
		if (ch != 'q')
		{
			clear();
			helpLoop();
			return 0;
		}
	}
	clear();

	return 1;
}

