#include "FonctionsPacMan.h"
#define POWER_STATE 60

void initSquare(Square *sqrt)
{
	sqrt->object = none;
	sqrt->person = no_one;
}

void initGhost(Ghost *a_ghost)
{
	a_ghost->x=0;
	a_ghost->y=0;
	a_ghost->state=0;
	a_ghost->snail=0;
	a_ghost->color=RED;
	a_ghost->chase=0;
}


void afficheSquare(Square *sqrt)
{
	if (sqrt->person == no_one)
	{
		switch(sqrt->object)
				{
					case ball: printw("\u00b7");
						break;
					case superball: printw("\u2022");
						break;
					case cherry: printw("\u0cb9");
						break;
					case strawberry: printw("\ua89e");
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
void moveGhost(Square* grid_old,Square* grid_new,int* pos_x,int* pos_y,Ghost* a_ghost,int* power_state, int* loop_game,int ghost_move)
{
	
	//direction où se bougent les fantômes
	switch(ghost_move)
	{
		case UP:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				a_ghost->y--;
				grid_new->person=ghost;
			}
			
			break;
		case DOWN:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				a_ghost->y++;
				grid_new->person=ghost;
			}
			break;
		case LEFT:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				a_ghost->x--;
				grid_new->person=ghost;
			}
			break;
		case RIGHT:
			if(grid_new->object != wallL && grid_new->object != wallH)
			{
				grid_old->person=no_one;
				a_ghost->x++;
				grid_new->person=ghost;
			}
			break;
		case NO_MOVE:
			a_ghost->x = a_ghost->x;
			a_ghost->y = a_ghost->y;
		default:
		printf("ERROR: a ghost can't move in this direction!\n");
	}
}

void ghostMoveChoice(Ghost* a_ghost,int* power_state,int* ghost_move,int* pos_x,int* pos_y,int* tour, Square* pac_man)
{
	int pos_x_guess=*pos_x;
	int pos_y_guess=*pos_y;
	//fuite dans fantomes lors du power_state
			if (*power_state != 0)
			{
				//fantome qui c'est fait manger
				if (a_ghost->state !=0)
					*ghost_move=NO_MOVE;
				else
				{
					//1 coup sur 2, le fantôme n'avance pas lors du power state
					if (a_ghost->snail == 0 )
					{
						//le fantôme fuit dans la direction opposé à Pac Man
						if(abs(a_ghost->x-*pos_x) > abs(a_ghost->y-*pos_y))
						{
							if((a_ghost->x-*pos_x)<0)
								*ghost_move=LEFT;
							else
								*ghost_move=RIGHT;
						}
						else
						{
							if((a_ghost->y-*pos_y)<0)
								*ghost_move=UP;
							else
								*ghost_move=DOWN;
						}
						a_ghost->snail=1;
					}
					else
					{
						*ghost_move=NO_MOVE;
						a_ghost->snail=0;
					}	
				}
			}
			else
			{
				if(a_ghost->chase != 0)
				{
					//mouvement des différents fantômes
					switch(a_ghost->color)
					{
						case ORANGE:
							*ghost_move=rand()%4;
							break;
						case ROSE:
								switch (pac_man->person)
								{
									case pac_man_down:
										pos_y_guess=pos_y_guess+2;
										break;
									case pac_man_up:
										pos_y_guess=pos_y_guess-2;
										break;
									case pac_man_left:
										pos_x_guess=pos_x_guess-2;
										break;
									case pac_man_right:
										pos_x_guess=pos_x_guess+2;
										break;
									default:
										pos_x_guess=pos_x_guess+2;
								}
								if(abs(a_ghost->x-pos_x_guess) > abs(a_ghost->y-pos_y_guess))
								{
									if((a_ghost->x-pos_x_guess)<0)
										*ghost_move=RIGHT;
									else
										*ghost_move=LEFT;
								}
								else
								{
									if((a_ghost->y-pos_y_guess)<0)
										*ghost_move=DOWN;
									else
										*ghost_move=UP;
								}
							break;
						case RED:
							if(abs(a_ghost->x-*pos_x) > abs(a_ghost->y-*pos_y))
							{
								if((a_ghost->x-*pos_x)<0)
									*ghost_move=RIGHT;
								else
									*ghost_move=LEFT;
							}
							else
							{
								if((a_ghost->y-*pos_y)<0)
									*ghost_move=DOWN;
								else
									*ghost_move=UP;
							}
							break;
						case CYAN:
							if(abs(a_ghost->x-*pos_x) > abs(a_ghost->y-*pos_y))
							{
								if((a_ghost->x-*pos_x)<0)
									*ghost_move=RIGHT;
								else
									*ghost_move=LEFT;
							}
							else
							{
								if((a_ghost->y-*pos_y)<0)
									*ghost_move=DOWN;
								else
									*ghost_move=UP;
							}
							break;
						default:
							printw("what color?\n");
					}
					a_ghost->chase--;
				}
				else
				{
					*ghost_move=rand()%4;
				}
				if(*tour % 80==0)
					switch(a_ghost->color)
					{
						case RED:
							a_ghost->chase=60;
							break;
						case ROSE:
							a_ghost->chase=50;
							break;
						case CYAN:
							a_ghost->chase=35;
							break;
						case ORANGE:
							a_ghost->chase=25;
							break;
						default:
							printw("what color?\n");
					}
					
			}
}
