#include <stdio.h>
#include <stdlib.h>

#include "tile.h"

tile** allocTiles(int h, int l) {
	tile** tl = malloc(sizeof(tile) * h);
	int i = 0;
	for(i=0; i<h; i++) {
		tl[i] = malloc(sizeof(tile) * l);
	}
	return tl;
}

void freeTiles(tile** tls, int h) {
	int i = 0;
	for(i=0; i<h; i++) {
		free(tls[i]);
	}
	free(tls);
}

void initTile(tile* tl, int x, int y, int flags) {
	tl->x = x; 
	tl->y = y;
	tl->flags = flags;
}

void printTile(tile* tl) {
	if(tl->flags & GUY) {
		printf("%s %s %s", YEL, "O_O", NRM);
	}
	else if(tl->flags & IN) {
		printf("%s %s  %s", RED, "IN", NRM);
	}
	else if(tl->flags & ROCK) {
		printf("%s  ·  %s", BLU, NRM);
	}
	else {
		if(tl->flags & OUT)
			printf("%s %s %s", BLU, "OUT", NRM);
		else
			printf("%5c", ' ');
	}
}

void printTileTop(tile* tl, tile* ttl) {
	if(ttl == NULL) {
		printf("+-----");
	}
	else {
		int wall1 = tl->flags & TOP_WALL; // top wall of the tile
		int wall2 = ttl->flags & BOTTOM_WALL; // bottom wal of the tile

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
		printf("|");
	}
	else {
		int wall1 = tl->flags & LEFT_WALL; // left wall of the tile
		int wall2 = ltl->flags & RIGHT_WALL; // right wall of the left tile
		
		if(wall1 || wall2) {
			printf("|");
		}
		else {
			printf(" ");
		}
	}
}