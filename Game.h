#ifndef __GAME_H__
#define __GAME_H__

#include <fstream>
#include <ncurses.h>
#include <termios.h>
#include "Character.h"

using namespace std;

class Game
{
public:
    int col;
    int row;
    int **data;
    bool isGamePlaying;

    Character cter;

public:
    Game()
    {
        ifstream ifstr;
        ifstr.open("data.txt");
        ifstr >> row >> col;
        data = new int *[col];
        for (int i = 0; i < col; i++)
        {
            data[i] = new int[row];
        }
        for (int y = 0; y < col; y++)
        {
            for (int x = 0; x < row; x++)
            {
                ifstr >> data[y][x];
            }
        }

        isGamePlaying = true;
        ifstr.close();
    }

    void Input()
    {
        cter.Move(getch(), data, row, col);
    }

    void Update()
    {
    }

    void Draw()
    {
        for (int y = 0; y < col; y++)
        {
            for (int x = 0; x < row; x++)
            {
                attron(COLOR_PAIR(data[y][x]));
                printw("%d", data[y][x]);
                attroff(COLOR_PAIR(data[y][x]));
            }
            printw("\n");
        }

        attron(COLOR_PAIR(cter.data));
        mvprintw(cter.y, cter.x, "%d", cter.data);
        attroff(COLOR_PAIR(cter.data));
        mvprintw(col, row, "");
    }

    ~Game()
    {
        for (int i = 0; i < col; i++)
        {
            delete data[i];
        }
        delete[] data;
    }
};

#endif