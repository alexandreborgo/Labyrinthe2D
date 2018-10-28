#ifndef HEADER_TILE
#define HEADER_TILE

#define NO_FLAG 0 		// 0000 0000 0000
#define LEFT_WALL 1		// 0000 0000 0001
#define BOTTOM_WALL 2	// 0000 0000 0010
#define RIGHT_WALL 4	// 0000 0000 0100
#define TOP_WALL 8 		// 0000 0000 1000
#define ALL_WALL 15		// 0000 0000 1111
#define IN 16 			// 0000 0001 0000
#define OUT 32 			// 0000 0010 0000 
#define GUY 64 			// 0000 0100 0000 
#define ROCK 128 		// 0000 1000 0000 
#define VISITED 256 	// 0001 0000 0000
#define CLEAN_FLAG 63	// 0000 0011 1111

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"

struct tl {
	int x;
  	int y;
	int flags;
};
typedef struct tl tile;

tile** allocTiles(int h, int l);
void initTile(tile* tl, int x, int y, int flags);
void freeTiles(tile** tls, int h);
void printTile(tile* tl);
void printTileTop(tile* tl, tile* ttl);
void printTileLeft(tile* tl, tile* ltl);

#endif
