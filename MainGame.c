#include <stdio.h>
#include <stdlib.h>

#include "FonctionsPacMan.h"
#define HAUTEUR 30
#define LARGEUR 50

int main()
{
	Square grid[LARGEUR][HAUTEUR];
	printf("\n");
	for(int j=0; j<HAUTEUR;j++)
	{
		for(int i=0; i<LARGEUR;i++)
		{
			initSquare(&grid[i][j]);
			if (i == LARGEUR/2 && j == HAUTEUR/2)
			{
				grid[j][i].object=none;
				grid[j][i].person=pac_man_right;
			}
			else
			{
				grid[j][i].object=ball;
			}
			afficheSquare(&grid[j][i]);
		}
		printf("\n");
	}
	return 0;
}
