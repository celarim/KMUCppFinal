#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <ncurses.h>
#include "Define.h"

class Character
{
public:
    int x;
    int y;
    int data;

public:
    Character()
    {
        x = 3;
        y = 2;
        data = CHARACTER;
    }

    void Move(char key, int** map, int mapx, int mapy)
    {
        int mx = x, my = y;
        int dx = 0, dy = 0;
        switch (key)
        {
        case 'w':
            y--;
            dy = -1;
            break;
        case 's':
            y++;
            dy = 1;
            break;
        case 'd':
            x++;
            dx = 1;
            break;
        case 'a':
            x--;
            dx = -1;
            break;
        }

        if(map[y][x] == BOX)
        {
            if(map[y + dy][x + dx] != WALL && map[y + dy][x + dx] != BOX)
            {
                map[y][x] = EMPTY;
                map[y + dy][x + dx] = BOX;
            }
            else
            {
                y = my;
                x = mx;
            }
        }
        else if (map[y][x] != EMPTY && map[y][x] != GOAL)
        {
            y = my;
            x = mx;
        }


        if (y < 0)
            y = 0;
        if (y > mapy - 1)
            y = mapy - 1;
        if (x < 0)
            x = 0;
        if (x > mapx - 1)
            x = mapx - 1;
    }
};

#endif