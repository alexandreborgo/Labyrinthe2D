#include <stdio.h>
#include <stdlib.h>

#include "tile.h"

tile* allocTile() {
	return (tile*) malloc(sizeof(tile*));
}

tile** allocTiles(int h, int l) {
	tile** tl = malloc(sizeof(tile) * h);
	int i = 0;
	for(i=0; i<h; i++) {
		tl[i] = malloc(sizeof(tile) * l);
	}
	return tl;
}


void freeTile(tile* tl) {
	free(tl);
}

void freeTiles(tile** tls, int h) {
	int i = 0;
	for(i=0; i<h; i++) {
		free(tls[i]);
	}
	free(tls);
}

void initTile(tile* tl, int x, int y, unsigned char wall) {
	tl->x = x; 
	tl->y = y;
	tl->wall = wall;
}

void printTile(tile tl) {
	printf("|%5c", ' ');
}

void printTileTop(tile* tl, tile* ttl) {
	if(ttl == NULL) {
		printf("+-----");
	}
	else {
		int wall1 = ((tl->wall >> 3) & 1);
		int wall2 = ((ttl->wall >> 3) & 1);

		if(wall1 || wall2) {
			printf("+-----");
		}
		else {
			printf("+     ");
		}
	}
}

void printTileLeft(tile* tl, tile* ltl) {
	if(ltl == NULL) {
		printf("|%5c", ' ');
	}
	else {
		int wall1 = ((tl->wall >> 2) & 1);
		int wall2 = ((ltl->wall >> 2) & 1);

		if(wall1 || wall2) {
			printf("|%5c", ' ');
		}
		else {
			printf(" %5c", ' ');
		}
	}
}