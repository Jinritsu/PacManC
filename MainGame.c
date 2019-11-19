#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
	
	init_pair(1, COLOR_YELLOW,COLOR_BLACK);
	//position de PAC MAN
	int pos_x;
	int pos_y;
	
	int power_state = 0;
	
	//positions des fantomes
	int ghost_x[4];
	int ghost_y[4];
	//état des fantomes(normal, affaibli,mangé)
	int ghost_state[4]={0,0,0,0};
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
						ghost_x[ind_ghost]=largeur;
						ghost_y[ind_ghost]=hauteur;
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
					ghost_x[0]=i;
					ghost_y[0]=j;
				}
				else if (i == LARGEUR*3/4 && j == HAUTEUR*3/4)
				{
					grid[j][i].object=ball;
					grid[j][i].person=ghost;
					ghost_x[1]=i;
					ghost_y[1]=j;
				}
				else if (i == LARGEUR*3/4 && j == HAUTEUR/4)
				{
					grid[j][i].object=ball;
					grid[j][i].person=ghost;
					ghost_x[2]=i;
					ghost_y[2]=j;
				}
				else if (i == LARGEUR/4 && j == HAUTEUR*3/4)
				{
					
					grid[j][i].person=ghost;
					ghost_x[3]=i;
					ghost_y[3]=j;
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
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y-1][pos_x],&pos_x,&pos_y,UP,&power_state);
				break;
			//mouvement bas
			case KEY_DOWN:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y+1][pos_x],&pos_x,&pos_y,DOWN,&power_state);
				break;
			//mouvement gauche
			case KEY_LEFT:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y][pos_x-1],&pos_x,&pos_y,LEFT,&power_state);
				break;
			//mouvement droite
			case KEY_RIGHT:
				movePacMan(&grid[pos_y][pos_x],&grid[pos_y][pos_x+1],&pos_x,&pos_y,RIGHT,&power_state);
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
			ghost_move=rand()%4;
			
			
			switch(ghost_move)
			{
				case UP:
					if(grid[ghost_y[i]-1][ghost_x[i]].object != wallL && grid[ghost_y[i]-1][ghost_x[i]].object != wallH)
					{
						grid[ghost_y[i]][ghost_x[i]].person=no_one;
						ghost_y[i]--;
						grid[ghost_y[i]][ghost_x[i]].person=ghost;
					}
					
					break;
				case DOWN:
					if(grid[ghost_y[i]+1][ghost_x[i]].object != wallL && grid[ghost_y[i]+1][ghost_x[i]].object != wallH)
					{
						grid[ghost_y[i]][ghost_x[i]].person=no_one;
						ghost_y[i]++;
						grid[ghost_y[i]][ghost_x[i]].person=ghost;
					}
					break;
				case LEFT:
					if(grid[ghost_y[i]][ghost_x[i]-1].object != wallL && grid[ghost_y[i]][ghost_x[i]-1].object != wallH)
					{
						grid[ghost_y[i]][ghost_x[i]].person=no_one;
						ghost_x[i]--;
						grid[ghost_y[i]][ghost_x[i]].person=ghost;
					}
					break;
				case RIGHT:
					if(grid[ghost_y[i]][ghost_x[i]+1].object != wallL && grid[ghost_y[i]][ghost_x[i]+1].object != wallH)
					{
						grid[ghost_y[i]][ghost_x[i]].person=no_one;
						ghost_x[i]++;
						grid[ghost_y[i]][ghost_x[i]].person=ghost;
					}
					break;
				default:
					printf("ERROR, a ghost can't move in another direction!");
			}
			if ( ghost_y[i] == pos_y && ghost_x[i]==pos_x && power_state!=0)
			{
				grid[ghost_y[i]][ghost_x[i]].person=no_one;
				ghost_state[i]=10;
				ghost_y[i]=HAUTEUR/2;
				ghost_x[i]=LARGEUR/2;
				grid[ghost_y[i]][ghost_x[i]].person=ghost;
			}
			else if ( ghost_y[i] == pos_y && ghost_x[i]==pos_x && ghost_state[i]==0)
			{
				printf("perdu! un fantôme vous a attrapé\n");
				loop_game = 0;
			}
			if (ghost_state[i]!=0)
			{
				ghost_state[i]--;
			}
			
		}
		if (power_state!=0)
		{
			power_state--;
		}
		
		
		
		//mise a jour interface
		clear();
		printw("\n");
		for(int j=0; j<HAUTEUR;j++)
		{
			for(int i=0; i<LARGEUR;i++)
			{
				if (grid[j][i].person == ghost)
					attron(COLOR_PAIR(1));
					
					
				afficheSquare(&grid[j][i]);
				
				if (grid[j][i].person == ghost)
					attroff(COLOR_PAIR(1));
			}
			printw("\n");
		}
		refresh();
	}
	attroff(COLOR_PAIR(1));
	ch = getch();
	endwin();
	return 0;
}
