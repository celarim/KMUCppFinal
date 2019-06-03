#include <ncurses.h>
#include "Game.h"

int main()
{
	Game game;
	initscr();
	resize_term(game.col * 2, game.row * 2);
	start_color();
	init_pair(0, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	//Game Loop
	while (game.isGamePlaying)
	{
		clear();
		game.Input();  //Input
		game.Update(); //Update
		game.Draw();   //Draw
		refresh();	 //Draw
	}

	endwin();

	return 0;
}
