#include "FonctionsPacMan.h"


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
	else
	{
		switch(sqrt->person)
		{
			case pac_man_up: printf("ᗢ");
				break;
			case pac_man_down: printf("ᗣ");
				break;
			case pac_man_left: printf("ᗤ");
				break;
			case pac_man_right: printf("ᗧ");
				break;
			case ghost: printf("👻");
				break;
			default: printf(" ");
		}
	}
}

