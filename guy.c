#include <stdio.h>
#include <stdlib.h>

#include "guy.h"

guy* allocGuy() {
	return malloc(sizeof(guy));
}

void initGuy(guy* g, int x, int y) {
    g->d = TOP;
    g->x = x;
    g->y = y;
}

void freeGuy(guy* g) {
    free(g);
}