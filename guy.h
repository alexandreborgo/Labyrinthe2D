#ifndef HEADER_GUY
#define HEADER_GUY

#include "tile.h"
#include "labyrinthe.h"

#define TOP 8 // 0000 1000
#define LEFT 1 // 0000 0001 
#define BOTTOM 2 // 0000 0010
#define RIGHT 4 // 0000 0100

struct guy {
	// coor
	int x;
	int y;

    // direction
    int d;
};
typedef struct guy guy;

guy* allocGuy();
void initGuy(guy* g, int x, int y);
void freeGuy(guy* g);

#endif
