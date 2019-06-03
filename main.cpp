#include <ncurses.h>
#include "Game.h"
#include "Define.h"

int main()
{
	Game game;
	initscr();
	resize_term(50, 50);

	WINDOW *win1;
	win1 = newwin(30, 30, 3, 2);
	game.window = win1;

	curs_set(0);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	start_color();
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_WHITE);
	init_pair(EMPTY, COLOR_WHITE, COLOR_WHITE);
	init_pair(WALL, COLOR_BLUE, COLOR_BLUE);
	init_pair(BOX, COLOR_GREEN, COLOR_GREEN);
	init_pair(GOAL, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(OUTSIDE, COLOR_CYAN, COLOR_CYAN);
	init_pair(CHARACTER, COLOR_MAGENTA, COLOR_WHITE);

	wbkgd(stdscr, COLOR_PAIR(10));
	wbkgd(win1, COLOR_PAIR(11));

	mvwprintw(stdscr, 1, 1, " BLOCK GAME");

	border('*', '*', '*', '*', '*', '*', '*', '*');
	refresh();

	//Game Loop
	while (game.isGamePlaying)
	{
		game.Update(); //Update
		game.Draw();  //Draw
		game.Input(); //Input
		refresh();
		wrefresh(win1);
		wclear(win1);
	}

	delwin(win1);
	endwin();

	return 0;
}
