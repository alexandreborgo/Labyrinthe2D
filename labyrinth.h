#ifndef HEADER_LABYRINTHE
#define HEADER_LABYRINTHE

#include "tile.h"

#define CHANCE 44

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"

typedef struct lab {
	// size
	int h;
	int l;

	// map
	tile** tiles;

	// in
	int x_in;
	int y_in;

	// out
	int x_ou;
	int y_ou;
	
} labyrinth;

labyrinth* allocLabyrinth();
void generateLabyrinth(labyrinth* lab, int h, int l);
int initLabyrinthFromFile(labyrinth* l, char* filename);
void saveLabyrinth(labyrinth* l, char* filename);
void displayLabyrinth2(labyrinth* lab);
void freeLabyrinth(labyrinth* lab);

#endif
