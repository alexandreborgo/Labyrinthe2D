#include <stdlib.h>
#include <stdio.h>

#include "labyrinthe.h"
#include "tile.h"
#include "play.h"

/* ==================== DEBUG ==================== */

void printBin2(int b) {
	int i;
	for(i=15; i>=0; i--)
		printf("%d", (b>>i)&1);
	printf("\n");
}

/* ==================== FUNC ==================== */

labyrinthe* allocLabyrinthe() {
	return malloc(sizeof(labyrinthe));
}

void freeLabyrinthe(labyrinthe* lab) {
	freeTiles(lab->tiles, lab->h);
	free(lab);
}

void initLabyrintheFromFile(labyrinthe* l, char* filename) {
	FILE* f = fopen(filename, "r");
	fscanf(f, "%d %d", &(l->h), &(l->l));
	l->tiles = allocTiles(l->h, l->l);

	fscanf(f, "%d %d", &(l->x_in), &(l->y_in));
	fscanf(f, "%d %d", &(l->x_ou), &(l->y_ou));

	int i, j;
	for(i=0; i<l->h; i++) {
		for(j=0; j<l->l; j++) {
			int tmp = 0;
			fscanf(f, "%d", &tmp);

			if(l->x_in == j && l->y_in == i) {
				tmp |= IN | GUY;
			}
			else if(l->x_ou == j && l->y_ou == i) {
				tmp |= OUT;
			}

			initTile(&(l->tiles[i][j]), j, i, tmp);
			printf("%d => ", tmp);
			printBin2(l->tiles[i][j].flags);
		}
	}
	fclose(f);
}

void saveLabyrinthe(labyrinthe* l, char* filename) {
	FILE* f = fopen(filename, "w");
	fprintf(f, "%d %d ", l->h, l->l);
	fprintf(f, "%d %d ", l->x_in, l->y_in);
	fprintf(f, "%d %d\n", l->x_ou, l->y_ou);

	int i, j;
	for(i=0; i<l->h; i++) {
		for(j=0; j<l->l; j++) {
			// keep only walls, in and out
			l->tiles[i][j].flags &= ~(VISITED | ROCK | GUY);
			fprintf(f, "%d ", l->tiles[i][j].flags);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void generateLabyrinthe(labyrinthe* lab, int h, int l) {
	lab->h = h;
	lab->l = l;
	lab->tiles = allocTiles(h, l);
	lab->x_in = rand() % lab->l;
	lab->y_in = rand() % lab->h;
	
	do {
		lab->x_ou = rand() % lab->l;
		lab->y_ou = rand() % lab->h;
		printf("%d %d\n", lab->x_ou, lab->y_ou);
	} while(lab->x_ou == lab->x_in && lab->y_ou == lab->y_in);

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
	
	if(!run_try(lab, &(lab->tiles[lab->y_in][lab->x_in]))) {
		// no path, so we generate another one
		freeTiles(lab->tiles, lab->h);
		generateLabyrinthe(lab, h, l);
	}
	else {
		// this block is inside a else to execute it only if a good labyrinthe is generated
		int i, j;
		for(i=0; i<lab->h; i++) {
			for(j=0; j<lab->l; j++) {
				lab->tiles[i][j].flags &= ~(VISITED);
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

