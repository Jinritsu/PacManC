#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#ifndef FONCTIONSPACMAN_H
#define FONCTIONSPACMAN_H

typedef enum Object
{none,ball,superball,cherry,strawberry,wallH,wallL}Object;

typedef enum Person
{no_one,pac_man_down,pac_man_up,pac_man_left,pac_man_right,ghost}Person;

typedef enum Direction
{UP,DOWN,RIGHT,LEFT}Direction;


typedef struct Square
{
	Object object;
	Person person;
}Square;

void initSquare(Square *sqrt);
void afficheSquare(Square *sqrt);
void movePacMan(Square* grid_old,Square* grid_new,int* pos_x,int* pos_y,int move,int* power_state);

#endif
