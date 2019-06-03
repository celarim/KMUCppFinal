#include <ncurses.h>
#include "Game.h"
#include "Define.h"

int main()
{
	Game game;
	initscr();
	resize_term(game.col * 2, game.row * 2);

	cbreak();
	noecho();
	nodelay(stdscr, TRUE);

	start_color();
	init_pair(EMPTY, COLOR_RED, COLOR_BLACK);
	init_pair(WALL, COLOR_BLUE, COLOR_BLACK);
	init_pair(BOX, COLOR_GREEN, COLOR_BLACK);
	init_pair(GOAL, COLOR_YELLOW, COLOR_BLACK);
	init_pair(OUTSIDE, COLOR_CYAN, COLOR_BLACK);
	init_pair(CHARACTER, COLOR_MAGENTA, COLOR_BLACK);
	//Game Loop
	while (game.isGamePlaying)
	{
		game.Update(); //Update
		game.Draw();   //Draw
		game.Input();  //Input
		refresh();	 //Draw
		clear();
	}

	endwin();

	return 0;
}
