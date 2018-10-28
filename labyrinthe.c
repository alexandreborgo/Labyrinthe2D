#include <stdlib.h>
#include <stdio.h>

#include "labyrinthe.h"
#include "tile.h"

labyrinthe* allocLabyrinthe() {
	return malloc(sizeof(labyrinthe));
}

void freeLabyrinthe(labyrinthe* lab) {
	freeTiles(lab->tiles, lab->h);
	free(lab);
}

void initLabyrinthe(labyrinthe* lab, int h, int l) {
	lab->h = h;
	lab->l = l;
	lab->tiles = allocTiles(h, l);

	int i, j;
	for(i=0; i<lab->h; i++) {
		for(j=0; j<lab->l; j++) {
			int flags = rand() % 15;
			initTile(&(lab->tiles[i][j]), i, j, flags);
		}
	}
}

void generateLabyrinthe(labyrinthe* lab, int h, int l) {
	lab->h = h;
	lab->l = l;
	lab->tiles = allocTiles(h, l);
	lab->x_in = rand() % lab->l;
	lab->y_in = rand() % lab->h;
	lab->x_ou = rand() % lab->l;
	lab->y_ou = rand() % lab->h;

	int i, j;
	for(i=0; i<lab->h; i++) {
		for(j=0; j<lab->l; j++) {
			int wall = 15;
			int flags = ALL_WALL;

			if(lab->x_in == j && lab->y_in == i) {
				flags |= IN | GUY;
			}
			else if(lab->x_ou == j && lab->y_ou == i) {
				flags |= OUT;
			}

			initTile(&(lab->tiles[i][j]), j, i, flags);
		}
	}

	for(i=0; i<lab->h; i++) {
		for(j=0; j<lab->l-1; j++) {
			if((rand() % 100) + 1 >= CHANCE) {
				lab->tiles[i][j].flags = lab->tiles[i][j].flags & ~RIGHT_WALL;
				lab->tiles[i][j+1].flags = lab->tiles[i][j+1].flags & ~LEFT_WALL;
			}
		}
	}

	for(i=0; i<lab->h-1; i++) {
		for(j=0; j<lab->l; j++) {
			if((rand() % 100) + 1 >= CHANCE) {
				lab->tiles[i][j].flags = lab->tiles[i][j].flags & ~BOTTOM_WALL;
				lab->tiles[i+1][j].flags = lab->tiles[i+1][j].flags & ~TOP_WALL;
			}
		}
	}
}

void displayLabyrinthe2(labyrinthe* lab) {
	int i, j, k;
	for(i=0; i<lab->h; i++) {
		for(j=0; j<lab->l; j++) {
			if(i > 0)
				printTileTop(&(lab->tiles[i][j]), &(lab->tiles[i-1][j]));
			else
				printTileTop(&(lab->tiles[i][j]), NULL);
		}
		printf("+\n");
		for(j=0; j<lab->l; j++) {
			if(j > 0)
				printTileLeft(&(lab->tiles[i][j]), &(lab->tiles[i][j-1]));
			else
				printTileLeft(&(lab->tiles[i][j]), NULL);
			printTile(&(lab->tiles[i][j]));
		}
		printf("|\n");	
	}
	for(k=0; k<lab->l; k++)  printf("+-----");
	printf("+\n");
}

