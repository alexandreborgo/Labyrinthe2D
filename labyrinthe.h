#ifndef HEADER_LABYRINTHE
#define HEADER_LABYRINTHE

#include "tile.h"

#define CHANCE 44

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
	
} labyrinthe;

labyrinthe* allocLabyrinthe();
void generateLabyrinthe(labyrinthe* lab, int h, int l);
void initLabyrintheFromFile(labyrinthe* l, char* filename);
void saveLabyrinthe(labyrinthe* l, char* filename);
void displayLabyrinthe2(labyrinthe* lab);
void freeLabyrinthe(labyrinthe* lab);

#endif
