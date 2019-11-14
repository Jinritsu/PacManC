#include "FonctionsPacMan.h"


void initSquare(Square *sqrt)
{
	sqrt->object = none;
	//sqrt->person = no_one;
}

void afficheSquare(Square *sqrt)
{
	switch(sqrt->object)
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

