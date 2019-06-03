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
    int **origindata;
    bool isGamePlaying;
    int GoalCount;
    int step;
    int push;
    int stage;
    WINDOW *window;

    Character cter;

public:
    Game() : cter(0, 0)
    {
        Init(1);
    }

    void Init(int stg)
    {
        GoalCount = 0;
        ifstream ifstr;
        char str[256];
        sprintf(str, "stage%d.txt", stg);
        ifstr.open(str);
        if (!ifstr.is_open())
        {
            isGamePlaying = false;
            return;
        }
        ifstr >> row >> col;
        data = new int *[col];
        origindata = new int *[col];
        for (int i = 0; i < col; i++)
        {
            data[i] = new int[row];
            origindata[i] = new int[row];
        }
        for (int y = 0; y < col; y++)
        {
            for (int x = 0; x < row; x++)
            {
                ifstr >> data[y][x];
                origindata[y][x] = data[y][x];
                if (data[y][x] == GOAL)
                {
                    GoalCount += 1;
                }
                if (data[y][x] == CHARACTER)
                {
                    cter.x = x;
                    cter.y = y;
                    data[y][x] = origindata[y][x] = 5;
                }
            }
        }

        isGamePlaying = true;
        step = 0;
        push = 0;
        stage = stg;
        ifstr.close();
    }

    void Input()
    {
        cter.Move(getch(), data, row, col, &step, &push);
    }

    void Update()
    {
        int gc = 0;
        for (int y = 0; y < col; y++)
        {
            for (int x = 0; x < row; x++)
            {
                if (origindata[y][x] == GOAL && data[y][x] == EMPTY)
                {
                    data[y][x] = GOAL;
                }
                else if (origindata[y][x] == GOAL && data[y][x] == BOX)
                {
                    gc++;
                }
            }
        }
        if (gc == GoalCount)
        {
            napms(100);

            ifstream ifstr;
            char str[256];
            sprintf(str, "stage%d.txt", ++stage);
            ifstr.open(str);
            if (!ifstr.is_open())
            {
                isGamePlaying = false;
                return;
            }
            ifstr.close();
            Release();
            Init(++stage);
            clear();
            border('*', '*', '*', '*', '*', '*', '*', '*');
            mvwprintw(stdscr, 1, 1, " BLOCK GAME");
            refresh();
        }
    }

    void Draw()
    {
        for (int y = 0; y < col; y++)
        {
            for (int x = 0; x < row; x++)
            {
                wattron(window, COLOR_PAIR(data[y][x]));
                mvwprintw(window, y + 1, x + 1, "=");
                wattroff(window, COLOR_PAIR(data[y][x]));
            }
        }

        wattron(window, COLOR_PAIR(cter.data));
        mvwprintw(window, cter.y + 1, cter.x + 1, "&");
        wattroff(window, COLOR_PAIR(cter.data));

        mvprintw(4, 38, "**INFO**");
        mvprintw(5, 38, "Step  : %d", step);
        mvprintw(6, 38, "Push  : %d", push);
        mvprintw(7, 38, "Stage : %d", stage);
    }

    void Release()
    {
        for (int i = 0; i < col; i++)
        {
            delete data[i];
            delete origindata[i];
        }
        delete[] data;
        delete[] origindata;
    }

    ~Game()
    {
        Release();
    }
};

#endif