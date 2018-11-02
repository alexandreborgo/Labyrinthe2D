#include <stdlib.h>
#include <stdio.h>

#include "labyrinth.h"
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

labyrinth* allocLabyrinth() {
	return malloc(sizeof(labyrinth));
}

void freeLabyrinth(labyrinth* lab) {
	freeTiles(lab->tiles, lab->h);
	free(lab);
}

int initLabyrinthFromFile(labyrinth* l, char* filename) {
	FILE* f = fopen(filename, "r");
	fscanf(f, "%d %d", &(l->h), &(l->l));
	l->tiles = allocTiles(l->h, l->l);

	fscanf(f, "%d %d", &(l->x_in), &(l->y_in));
	fscanf(f, "%d %d", &(l->x_ou), &(l->y_ou));
			
	if(l->x_ou < 0 || l->y_ou >= l->l) {
		printf("%sThe exit of the labyrinth is not in the labyrinth!%s\n", RED, NRM);
		freeLabyrinth(l);
		return -1;
	}

	if(l->x_in < 0 || l->y_in >= l->h) {
		printf("%sThe entrance of the labyrinth is not in the labyrinth!%s\n", RED, NRM);
		freeLabyrinth(l);
		return -1;
	}

	int i, j;
	for(i=0; i<l->h; i++) {
		for(j=0; j<l->l; j++) {
			int tmp = 0;
			fscanf(f, "%d", &tmp);

			if(l->x_in == j && l->y_in == i) {
				tmp |= IN | GUY;
			}
			if(l->x_ou == j && l->y_ou == i) {
				tmp |= OUT;
			}

			initTile(&(l->tiles[i][j]), j, i, tmp);
		}
	}
	fclose(f);

	// check if the lab is coherent

	int errors = 0;

	if(l->x_ou == l->x_in && l->y_ou == l->y_in) {
		printf("%sThe exit of the labyrinth is on the same case as the entrance!%s\n", RED, NRM);
		errors++;
	}

	for(i=0; i<l->h; i++) {
		for(j=0; j<l->l-1; j++) {			
			int wall1 = l->tiles[i][j].flags & RIGHT_WALL;
			int wall2 = l->tiles[i][j+1].flags & LEFT_WALL;
			if(wall1 == RIGHT_WALL && wall2 != LEFT_WALL || wall1 != RIGHT_WALL && wall2 == LEFT_WALL) {
				errors++;
				printf("%sError on the wall between case (%d,%d) and case (%d,%d)!%s\n", RED, j, i, j+1, i, NRM);
			}
		}
	}
	for(i=0; i<l->h-1; i++) {
		for(j=0; j<l->l; j++) {
			int wall1 = l->tiles[i][j].flags & BOTTOM_WALL;
			int wall2 = l->tiles[i+1][j].flags & TOP_WALL;
			if(wall1 == BOTTOM_WALL && wall2 != TOP_WALL || wall1 != BOTTOM_WALL && wall2 == TOP_WALL) {
				errors++;
				printf("%sError on the wall between case (%d,%d) and case (%d,%d)!%s\n", RED, j, i, j, i+1, NRM);
			}
		}
	}
	return errors;		
}

void saveLabyrinth(labyrinth* l, char* filename) {
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

void generateLabyrinth(labyrinth* lab, int h, int l) {
	lab->h = h;
	lab->l = l;
	lab->tiles = allocTiles(h, l);
	lab->x_in = rand() % lab->l;
	lab->y_in = rand() % lab->h;
	
	do {
		lab->x_ou = rand() % lab->l;
		lab->y_ou = rand() % lab->h;
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
		generateLabyrinth(lab, h, l);
	}
	else {
		// this block is inside a else to execute it only if a good labyrinth is generated
		int i, j;
		for(i=0; i<lab->h; i++) {
			for(j=0; j<lab->l; j++) {
				lab->tiles[i][j].flags &= ~(VISITED);
			}
		}
	}
}

void displayLabyrinth2(labyrinth* lab) {
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

