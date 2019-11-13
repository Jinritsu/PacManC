#include "FonctionsPacMan.h"


void initSquare(Square sqrt)
{
	sqrt.object = none;
	sqrt.person = no_one;
}

void initGrid(Square** grid, int largeur, int hauteur)
{
	 for(int i; i>largeur; i++)
	{
		for(int j; j>hauteur; j++)
		{
			initSquare(grid[i][j]);
		}
	}
}

void afficheGrid(Square** grid, int largeur, int hauteur)
{
	for(int i; i>largeur; i++)
	{
		for(int j; j>hauteur; j++)
		{
			switch(grid[i][j].object)
			{
				case ball: printf("⋅");
					break;
				case superball: printf("●");
					break;
				case cherry: printf("🍒");
					break;
				case strawberry: printf("🍓");
					break;
				case wallH: printf("┃");
					break;
				case wallL: printf("━");
					break;
				default: printf(" ");
			}
		}
		printf("\n");
	}
}
