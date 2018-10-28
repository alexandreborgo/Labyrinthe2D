#ifndef HEADER_TILE
#define HEADER_TILE

#define TOP_WALL 8 // 0000 1000
#define LEFT_WALL 1 // 0000 0001
#define BOTTOM_WALL 2 // 0000 0010
#define RIGHT_WALL 4 // 0000 0100

#define NO_FLAG 0 // 0000 0000
#define IN 1 // 0000 0001
#define OUT 2 // 0000 0010
#define GUY 4 // 0000 0100
#define ROCK 8 // 0000 1000
#define VISITED 16 // 0001 0000

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"

struct tl {
	int x;
  	int y;
    int wall;
	unsigned char flags;
};
typedef struct tl tile;

tile** allocTiles(int h, int l);
void initTile(tile* tl, int x, int y, int wall, unsigned char flags);
void freeTiles(tile** tls, int h);
void printTile(tile* tl);
void printTileTop(tile* tl, tile* ttl);
void printTileLeft(tile* tl, tile* ltl);

#endif
