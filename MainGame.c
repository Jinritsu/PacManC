#include <stdio.h>
#include <stdlib.h>
#define HAUTEUR 30
#define LARGEUR 30

int main()
{
	Square grid[LARGEUR][HAUTEUR];
	for(int i; i>LARGEUR; i++)
	{
		for(int j; j>HAUTEUR; j++)
		{
			intiSquare(grid[i][j]);
		}
	}
	return 0;
}
