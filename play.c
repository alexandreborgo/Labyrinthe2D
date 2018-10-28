#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "play.h"
#include "labyrinthe.h"
#include "tile.h"

/* ==================== DEBUG ==================== */
void printBin(int b) {
	int i;
	for(i=15; i>=0; i--)
		printf("%d", (b>>i)&1);
	printf("\n");
}

void printDir(int dir) {
    if(dir == TOP)
        printf("TOP\n");
    else if(dir == LEFT)
        printf("LEFT\n");
    else if(dir == RIGHT)
        printf("RIGHT\n");
    else if(dir == BOTTOM)
        printf("BOTTOM\n");
    else
        printf("ERROR\n");
}

/* ==================== FUNC ==================== */

tile* getCaseInDir(labyrinthe* l, tile* t, int dir) {
    if(dir == TOP)
        return &(l->tiles[t->y-1][t->x]);
    else if(dir == LEFT)
        return &(l->tiles[t->y][t->x-1]);
    else if(dir == RIGHT)
        return &(l->tiles[t->y][t->x+1]);
    else if(dir == BOTTOM)
        return &(l->tiles[t->y+1][t->x]);
}

void display(labyrinthe* l) {
    system("clear");
	displayLabyrinthe2(l);
    sleep(1);
}

/* depth-first search */
int run2(labyrinthe* l, tile* t) {
    t->flags |= ROCK;
    t->flags |= GUY;

    display(l);

    if(t->flags & OUT) return 1;
    
    t->flags |= VISITED;
    
    char dir;
    for(dir=LEFT; dir<=TOP; dir=dir<<1) {        
        // check if there's a wall
        printDir(dir);
        printBin(t->flags);
        printBin(dir);
        printf("\n");
        char c;
        scanf("%c", &c);
        if(!(t->flags & dir)) {
            // check if the guy already visited the tile or not
            tile* tl = getCaseInDir(l, t, dir);
            if(!(tl->flags & VISITED)) {
                t->flags &= ~GUY;
                if(run2(l, tl) == 1) {
                    return 1;
                }
                t->flags |= GUY;
                display(l);
            }
        }
    }
    t->flags &= ~ROCK;
    t->flags &= ~GUY;
    return 0;
}