#include <stdio.h>
#include <stdlib.h>
#define HAUTEUR 30
#define LARGEUR 30


struct Square
{
	int x;
	int y;
	char symbol;
	Square* haut;
	Square* bas;
	Square* gauche;
	Square* droite;
	
}
typedef struct Square Square;

int main()
{
	return 0;
}
