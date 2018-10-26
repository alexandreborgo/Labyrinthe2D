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
			unsigned char wall = (unsigned char) rand() % 128;
			initTile(&(lab->tiles[i][j]), i, j, wall);
		}
	}
}

void displayLabyrinthe(labyrinthe* lab) {
	int i, j, k;
	for(i=0; i<lab->h; i++) {
		for(k=0; k<lab->l; k++)  printf("+-----");
		printf("+\n");
		for(j=0; j<lab->l; j++) {
			printTile(lab->tiles[i][j]);
		}
		printf("|\n");
	}
	for(k=0; k<lab->l; k++)  printf("+-----");
	printf("+\n");
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

		}
		printf("|\n");	
	}
	for(k=0; k<lab->l; k++)  printf("+-----");
	printf("+\n");
}

