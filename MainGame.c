#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <ncurses.h>
#include <curses.h>

#include "FonctionsPacMan.h"



int main(int argc, char* argv[])
{
	//taille de grille
	const int HAUTEUR=30;
	const int LARGEUR=50;
	//initalisation de la fenetre
	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	cbreak();
	start_color();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	timeout(1000);
	
	//score de jeu
	int score=0;
	int score2=0;
	
	//position de PAC MAN
	int pos_x;
	int pos_y;
	
	int power_state = 0;
	
	//fantomes
	Ghost ghosts[4];
	for (int i=0;i<4;i++)
	{
		initGhost(&ghosts[i]);
		switch(i)
		{
			case 0:
				ghosts[i].color=RED;
				init_pair(1, COLOR_RED,COLOR_BLACK);
				break;
			case 1:
				ghosts[i].color=ROSE;
				init_pair(2, COLOR_MAGENTA,COLOR_BLACK);
				break;
			case 2:
				ghosts[i].color=CYAN;
				init_pair(3, COLOR_CYAN,COLOR_BLACK);
				break;
			case 3:
				ghosts[i].color=ORANGE;
				init_pair(4, COLOR_YELLOW,COLOR_BLACK);
				break;
			default:
				printf("What color?\n");
		}
	}
	init_pair(5, COLOR_BLUE,COLOR_BLACK);
	Coloration a_color=CYAN;
	//tours de jeu (pour les fantomes)
	int tour=0;
	//déplacement des fantomes
	int ghost_move;
	//grille de jeu
	Square grid[HAUTEUR][LARGEUR];
	//Vérification des arguments de lancement
	if (argc!=1)
	{
		char* filename = argv[1];
		FILE* niveau=NULL;
		niveau = fopen(filename,"r");
		//Vérification que le pointeur ne mène pas à nulle part
		if (niveau == NULL)
		{
			printf("ERROR: No file found, or file not correct\n");
			printf("ending...\n");
			endwin();
			exit(0);
			
			
			
		}
		else
		{
			int largeur=0;
			int hauteur=0;
			int caractere_actuel=0;
			int ind_ghost=0;
			printw("score: %d",score);
			printw("\n");
			//grille de jeu
			do
			{
				initSquare(&grid[hauteur][largeur]);
				caractere_actuel = fgetc(niveau); // On lit le caractère
				switch(caractere_actuel)
				{
					//printf("%c", caractere_actuel);
					//lecture du fichier et affectation des cases avec le fichier
					case 'H':
						grid[hauteur][largeur].object=wallH;
						afficheSquare(&grid[hauteur][largeur]);
						largeur++;
						break;
					case 'L':
						grid[hauteur][largeur].object=wallL;
						afficheSquare(&grid[hauteur][largeur]);
						largeur++;
						break;
					case 'b':
						grid[hauteur][largeur].object=ball;
						afficheSquare(&grid[hauteur][largeur]);
						largeur++;
						break;
					case 'B':
						grid[hauteur][largeur].object=superball;
						afficheSquare(&grid[hauteur][largeur]);
						largeur++;
						break;
					case 'G':
						grid[hauteur][largeur].object=ball;
						grid[hauteur][largeur].person=ghost;
						ghosts[ind_ghost].x=largeur;
						ghosts[ind_ghost].y=hauteur;
						afficheSquare(&grid[hauteur][largeur]);
						ind_ghost++;
						largeur++;
						
						break;
					case 'P':
						grid[hauteur][largeur].object=none;
						grid[hauteur][largeur].person=pac_man_left;
						afficheSquare(&grid[hauteur][largeur]);
						pos_x=largeur;
						pos_y=hauteur;
						largeur++;
						
						break;
					case 'C':
						grid[hauteur][largeur].object=cherry;
						afficheSquare(&grid[hauteur][largeur]);
						largeur++;
						break;
					case 'S':
						grid[hauteur][largeur].object=strawberry;
						afficheSquare(&grid[hauteur][largeur]);
						largeur++;
						break;
					case '\n':
						largeur = 0;
						hauteur++;
						printw("\n");
						break;
					case EOF:
						printf("finished.Creating level...\n");
						break;
					default:
						printf("ERROR: character not handled\n");
						endwin();
						exit(0);
				}
				
			}while (caractere_actuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
			printw("\n");
			fclose(niveau);
		}
	}
	else
	{
		
		//initialisation de l'interface
		printw("\n");
		//boucle sur les colonnes
		for(int j=0; j<HAUTEUR;j++)
		{
			//boucle sur les lignes
			for(int i=0; i<LARGEUR;i++)
			{
				//initialisation des cases 
				//(pour éviter qu'il y a tout et n'importe quoi)
				initSquare(&grid[j][i]);
				//affectation des objets et des personnages
				if (i == LARGEUR/2 && j == HAUTEUR/2)
				{
					grid[j][i].object=none;
					grid[j][i].person=pac_man_left;
					pos_x=i;
					pos_y=j;
				}
				else if (i == LARGEUR/4 && j == HAUTEUR/4)
				{
					grid[j][i].object=ball;
					grid[j][i].person=ghost;
					ghosts[0].x=i;
					ghosts[0].y=j;
				}
				else if (i == LARGEUR*3/4 && j == HAUTEUR*3/4)
				{
					grid[j][i].object=ball;
					grid[j][i].person=ghost;
					ghosts[1].x=i;
					ghosts[1].y=j;
				}
				else if (i == LARGEUR*3/4 && j == HAUTEUR/4)
				{
					grid[j][i].object=ball;
					grid[j][i].person=ghost;
					ghosts[2].x=i;
					ghosts[2].y=j;
				}
				else if (i == LARGEUR/4 && j == HAUTEUR*3/4)
				{
					grid[j][i].object=ball;
					grid[j][i].person=ghost;
					ghosts[3].x=i;
					ghosts[3].y=j;
				}
				else if (i == 0 || i == LARGEUR-1)
					grid[j][i].object=wallH;
				else if (j == 0 || j == HAUTEUR-1)
					grid[j][i].object=wallL;
				else
					grid[j][i].object=ball;
					
					
				afficheSquare(&grid[j][i]);
			}
		printw("\n");
		}
	}
	//carcatere d'entrée du clavier
	int ch;
	//boucle de jeu
	int loop_game=1;
	while(loop_game)
	{
		ch=getch();
		//mouvements de Pac Man
		//mouvement haut 
		switch(ch)
		{
			case KEY_UP:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y-1][pos_x],&pos_x,&pos_y,UP,&power_state, &score);
				break;
			//mouvement bas
			case KEY_DOWN:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y+1][pos_x],&pos_x,&pos_y,DOWN,&power_state, &score);
				break;
			//mouvement gauche
			case KEY_LEFT:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y][pos_x-1],&pos_x,&pos_y,LEFT,&power_state, &score);
				break;
			//mouvement droite
			case KEY_RIGHT:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y][pos_x+1],&pos_x,&pos_y,RIGHT,&power_state, &score);
				break;
			//quitter le jeu
			case 'q':
				loop_game = 0;
				break;
			default:
				ch=ERR;
		}
		//mouvements fantomes
		for (int i = 0; i < 4; i++)
		{
			ghostMoveChoice(&ghosts[i],&power_state,&ghost_move,&pos_x,&pos_y,&tour,&grid[pos_y][pos_x]);
			if ( ghosts[i].y == pos_y && ghosts[i].x==pos_x && power_state!=0)
			{
				moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[HAUTEUR/2][LARGEUR/2],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
				ghosts[i].x=LARGEUR/2;
				ghosts[i].y=HAUTEUR/2;
				ghosts[i].state=10;
			}
			else if ( ghosts[i].y == pos_y && ghosts[i].x==pos_x && ghosts[i].state==0)
			{
				loop_game = 0;
			}
			//direction où se bougent les fantômes
			switch(ghost_move)
			{
				case UP:
					moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[ghosts[i].y-1][ghosts[i].x],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
					break;
				case DOWN:
					moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[ghosts[i].y+1][ghosts[i].x],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
					break;
				case LEFT:
					moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[ghosts[i].y][ghosts[i].x-1],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
					break;
				case RIGHT:
					moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[ghosts[i].y][ghosts[i].x+1],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
					break;
				case NO_MOVE:
					moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[ghosts[i].y][ghosts[i].x],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
				default:
				printf("ERROR: a ghost can't move in this direction!\n");
			}
			if ( ghosts[i].y == pos_y && ghosts[i].x==pos_x && power_state!=0)
			{
				moveGhost(&grid[ghosts[i].y][ghosts[i].x],&grid[HAUTEUR/2][LARGEUR/2],&pos_x,&pos_y,&ghosts[i],&power_state, &loop_game,ghost_move);
				ghosts[i].x=LARGEUR/2;
				ghosts[i].y=HAUTEUR/2;
				ghosts[i].state=10;
			}
			else if ( ghosts[i].y == pos_y && ghosts[i].x==pos_x && ghosts[i].state==0)
			{
				loop_game = 0;
			}
			if (ghosts[i].state!=0)
			{
				ghosts[i].state--;
			}
			
		}
		if (power_state!=0)
		{
			power_state--;
		}
		
		
		
		//mise a jour interface
		clear();
		printw("score: %d",score);
		printw("\n");
		for(int j=0; j<HAUTEUR;j++)
		{
			for(int i=0; i<LARGEUR;i++)
			{
				//couleur des fantomes
				if (grid[j][i].person == ghost)
				{
					
					if(power_state==0)
					{
						for (int k=0;k<4;k++)
						{
							if (ghosts[k].x==i && ghosts[k].y==j)
								a_color=ghosts[k].color;
						}
						switch(a_color)
						{
							case RED:
								attron(COLOR_PAIR(1));
								break;
							case ROSE:
								attron(COLOR_PAIR(2));
								break;
							case CYAN:
								attron(COLOR_PAIR(3));
								break;
							case ORANGE:
								attron(COLOR_PAIR(4));
								break;
							default:
								printf("What color?\n");
						}
					}
					else
						attron(COLOR_PAIR(5));
				}	
				afficheSquare(&grid[j][i]);
				
				//enlever la couleur des fantomes
				if (grid[j][i].person == ghost)
				{
					if(power_state==0)
					{
						switch(a_color)
						{
							case RED:
								attroff(COLOR_PAIR(1));
								break;
							case ROSE:
								attroff(COLOR_PAIR(2));
								break;
							case CYAN:
								attroff(COLOR_PAIR(3));
								break;
							case ORANGE:
								attroff(COLOR_PAIR(4));
								break;
							default:
								printf("What color?\n");
						}
					}
					else
						attroff(COLOR_PAIR(5));
				}		
			}
			printw("\n");
		}
		tour++;
		if (tour > 3600)
			tour=0;
		refresh();
	}
	printw("perdu! un fantôme vous a attrapé\n");
	refresh();
	ch = getch();
	endwin();
	return 0;
}
