#include "FonctionsPacMan.h"
#define POWER_STATE 60

void initSquare(Square *sqrt)
{
	sqrt->object = none;
	sqrt->person = no_one;
}

void afficheSquare(Square *sqrt)
{
	if (sqrt->person == no_one)
	{
		switch(sqrt->object)
				{
					case ball: printw("\u2022");
						break;
					case superball: printw("\u25cf");
						break;
					case cherry: printw("🍒");
						break;
					case strawberry: printw("🍓");
						break;
					case wallH: printw("\u2503");
						break;
					case wallL: printw("\u2501");
						break;
					default: printw(" ");
				}
	}
	else
	{
		switch(sqrt->person)
		{
			case pac_man_up: printw("ᗢ");
				break;
			case pac_man_down: printw("ᗣ");
				break;
			case pac_man_left: printw("ᗤ");
				break;
			case pac_man_right: printw("ᗧ");
				break;
			case ghost: printw("\u1649");
				break;
			default: printw(" ");
		}
	}
}

void movePacMan(Square* grid_old,Square* grid_new,int* pos_x,int* pos_y,int move,int* power_state)
{
	if(grid_new->object == superball)
		*power_state = POWER_STATE;
	switch(move){
		case UP:
			if(grid_new->object != wallL && grid_new->object != wallH)
					{
						grid_old->person=no_one;
						*pos_y= *pos_y-1;
						grid_new->object = none;
						grid_new->person=pac_man_up;
					}
					else
						grid_old->person=pac_man_up;
			break;
		case DOWN:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				*pos_y= *pos_y+1;
				grid_new->object = none;
				grid_new->person=pac_man_down;
			}
			else
				grid_old->person=pac_man_down;
			break;
		case LEFT:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				*pos_x= *pos_x-1;
				grid_new->object = none;
				grid_new->person=pac_man_left;
			}
			else
				grid_old->person=pac_man_left;
			break;
		case RIGHT:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				*pos_x= *pos_x+1;
				grid_new->object = none;
				grid_new->person=pac_man_right;
			}
			else
				grid_old->person=pac_man_right;
			break;
		default:
			*pos_x=*pos_x;
			*pos_y=*pos_y;
		}
}

