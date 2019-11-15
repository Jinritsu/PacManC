#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>

#include "FonctionsPacMan.h"
#define HAUTEUR 30
#define LARGEUR 50

int main()
{
	//initalisation
	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	
	//position de PAC MAN
	int pos_x;
	int pos_y;
	
	//grille de jeu
	Square grid[HAUTEUR][LARGEUR];
	//charactere d'entrée du clavier
	int ch;
	
	//initialisation de l'interface
	printw("\n");
	for(int j=0; j<HAUTEUR;j++)
	{
		for(int i=0; i<LARGEUR;i++)
		{
			initSquare(&grid[j][i]);
			if (i == LARGEUR/2 && j == HAUTEUR/2)
			{
				grid[j][i].object=none;
				grid[j][i].person=pac_man_left;
				pos_x=i;
				pos_y=j;
			}
			else if (i == 0 || i == LARGEUR-1)
				grid[j][i].object=wallH;
			else if (j == 0 || j == HAUTEUR-1)
				grid[j][i].object=wallL;
			else
				grid[j][i].object=ball;
				
				
			afficheSquare(&grid[j][i]);
		}
		printw("\n");
	}
	int loop_game=1;
	while(loop_game)
	{
		ch=getch();
		if(ch == KEY_UP)
		{
			if(grid[pos_y-1][pos_x].object != wallL && grid[pos_y-1][pos_x].object != wallH)
			{
				grid[pos_y][pos_x].person=no_one;
				pos_y--;
				grid[pos_y][pos_x].object = none;
				grid[pos_y][pos_x].person=pac_man_up;
			}
			else
				grid[pos_y][pos_x].person=pac_man_up;
		}
		else if(ch == KEY_DOWN)
		{
			if(grid[pos_y+1][pos_x].object != wallL && grid[pos_y+1][pos_x].object != wallH)
			{
				grid[pos_y][pos_x].person=no_one;
				pos_y++;
				grid[pos_y][pos_x].object = none;
				grid[pos_y][pos_x].person=pac_man_down;
			}
			else
				grid[pos_y][pos_x].person=pac_man_down;
		}
		else if(ch == KEY_LEFT)
		{
			if(grid[pos_y][pos_x-1].object != wallL && grid[pos_y][pos_x-1].object != wallH)
			{
				grid[pos_y][pos_x].person=no_one;
				pos_x--;
				grid[pos_y][pos_x].object = none;
				grid[pos_y][pos_x].person=pac_man_left;
			}
			else
				grid[pos_y][pos_x].person=pac_man_left;
		}
		else if(ch == KEY_RIGHT)
		{
			if(grid[pos_y][pos_x+1].object != wallL && grid[pos_y][pos_x+1].object != wallH)
			{
				grid[pos_y][pos_x].person=no_one;
				pos_x++;
				grid[pos_y][pos_x].object = none;
				grid[pos_y][pos_x].person=pac_man_right;
			}
			else
				grid[pos_y][pos_x].person=pac_man_right;
		}
		else if (ch == 'q')
			loop_game = 0;
		
		clear();
		refresh();
		printw("\n");
		for(int j=0; j<HAUTEUR;j++)
		{
			for(int i=0; i<LARGEUR;i++)
			{
				afficheSquare(&grid[j][i]);
			}
			printw("\n");
		}
		refresh();
	}
	endwin();
	return 0;
}
