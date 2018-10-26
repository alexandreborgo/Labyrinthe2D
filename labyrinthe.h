#ifndef HEADER_LABYRINTHE
#define HEADER_LABYRINTHE

#include "tile.h"

struct lab {
	int h;
	int l;
	tile** tiles;
};
typedef struct lab labyrinthe;


labyrinthe* allocLabyrinthe();
void initLabyrinthe(labyrinthe* lab, int h, int l);
void displayLabyrinthe(labyrinthe* lab);
void displayLabyrinthe2(labyrinthe* lab);
void freeLabyrinthe(labyrinthe* lab);

#endif
