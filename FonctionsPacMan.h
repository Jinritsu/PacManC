#include <stdio.h>
#include <stdlib.h>
#ifndef FONCTIONSPACMAN_H
#define FONCTIONSPACMAN_H

typedef enum Object
{none,ball,superball,cherry,strawberry,wallH,wallL}Object;

typedef enum Person
{no_one,pac_man_down,pac_man_up,pac_man_left,pac_man_right,ghost}Person;

typedef struct Square
{
	Object object;
	Person person;
}Square;

void initSquare(Square *sqrt);
void afficheSquare(Square *sqrt);

#endif
