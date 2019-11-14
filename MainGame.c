#include <stdio.h>
#include <stdlib.h>

#include "FonctionsPacMan.h"
#define HAUTEUR 30
#define LARGEUR 30

int main()
{
	Square sqrt;
	initSquare(&sqrt);
	sqrt.object = superball;
	afficheSquare(&sqrt);
	printf("\n");
	return 0;
}
