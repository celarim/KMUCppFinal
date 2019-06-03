#include <iostream>
#include <fstream>
#include <ncurses.h>

using namespace std;

class Game
{
public:
    int col;
    int row;
    int **data;
    bool isGamePlaying;

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