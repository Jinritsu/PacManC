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

