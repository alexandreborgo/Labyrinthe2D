#ifndef HEADER_TILE
#define HEADER_TILE

struct tl {
	int x;
  	int y;
    char wall;
};
typedef struct tl tile;

tile* allocTile();
tile** allocTiles(int h, int l);
void initTile(tile* tl, int x, int y, unsigned char wall);
void freeTile(tile* tl);
void freeTiles(tile** tls, int h);
void printTile(tile tl);
void printTileTop(tile* tl, tile* ttl);
void printTileLeft(tile* tl, tile* ltl);

#endif
