#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "play.h"
#include "labyrinth.h"
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
// labyrinths/incoherent.lab
tile* getCaseInDir(labyrinth* l, tile* t, int dir) {
    if(dir == TOP) {
        if(t->y-1 >= 0) {
            return &(l->tiles[t->y-1][t->x]);
        }
    }
    else if(dir == LEFT) {
        if(t->x-1 >= 0) {
            return &(l->tiles[t->y][t->x-1]);
        }
    }
    else if(dir == RIGHT) {
        if(t->x+1 < l->l) {
            return &(l->tiles[t->y][t->x+1]);
        }
    }
    else if(dir == BOTTOM) {
        if(t->y+1 < l->h) {
            return &(l->tiles[t->y+1][t->x]);
        }
    }
    return NULL;
}

void display(labyrinth* l) {
    system("clear");
	displayLabyrinth2(l);
    sleep(1);
}

/* depth-first search */
int run2(labyrinth* l, tile* t) {
    t->flags |= ROCK;
    t->flags |= GUY;

    display(l);

    if(t->flags & OUT) return 1;
    
    t->flags |= VISITED;
    
    char dir;
    for(dir=LEFT; dir<=TOP; dir=dir<<1) {        
        // check if there's a wall
        if(!(t->flags & dir)) {
            tile* tl = getCaseInDir(l, t, dir);
            // check if the tile is inside the lab
            if(tl != NULL) {
                // check if the guy already visited the tile or not                
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
    }
    t->flags &= ~ROCK;
    t->flags &= ~GUY;
    return 0;
}

/*  same as run without display
    to find out if there's a solution
    in order to create coherant labyrinth
*/
int run_try(labyrinth* l, tile* t) {
    if(t->flags & OUT) return 1;    
    t->flags |= VISITED;    
    char dir;
    for(dir=LEFT; dir<=TOP; dir=dir<<1) {
        if(!(t->flags & dir)) {
            tile* tl = getCaseInDir(l, t, dir);
            if(!(tl->flags & VISITED)) {
                if(run_try(l, tl) == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}