#include <stdio.h>
#include <stdlib.h>
#ifndef FONCTIONSPACMAN_H
#define FONCTIONSPACMAN_H

typedef enum Object
{none,ball,superball,cherry,strawberry,wallH,wallL}Object;

typedef enum Person
{no_one,pac_man,ghost}Person;

typedef struct Square
{
	Object object;
	Person person;
}Square;

void initSquare(Square a_square);
void initGrid(Square** grid, int largeur, int hauteur);
void afficheGrid(Square** grid, int largeur, int hauteur);

#endif
