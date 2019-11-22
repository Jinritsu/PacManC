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
{UP,DOWN,RIGHT,LEFT,NO_MOVE}Direction;

typedef enum Coloration
{RED,ROSE,CYAN,ORANGE}Coloration;

typedef struct Ghost
{
	int x;
	int y;
	int state;
	int snail;
	int chase;
	Coloration color;
}Ghost;

typedef struct Square
{
	Object object;
	Person person;
}Square;

void initSquare(Square *sqrt);
void initGhost(Ghost *a_ghost);
void afficheSquare(Square *sqrt);
void movePacMan(Square* grid_old,Square* grid_new,int* pos_x,int* pos_y,int move,int* power_state,int* score);
void moveGhost(Square* grid_old,Square* grid_new,int* pos_x,int* pos_y,Ghost* a_ghost,int* power_state, int* loop_game,int ghost_move);
void ghostMoveChoice(Ghost* a_ghost,int* power_state,int* ghost_move,int* pos_x,int* pos_y,int* tour,Square* pac_man);

#endif
