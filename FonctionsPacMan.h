#include <stdio.h>
#include <stdlib.h>
#ifndef FONCTIONSPACMAN_H
#define FONCTIONSPACMAN_H

enum Object
{ball,superball,cherry,strawberry,wallH,wallL};

enum Person
{pac_man,ghost}

typedef struct Square
{
	Object object;
	Person person;
}Square;

void initSquare(Square a_square);


#endif
