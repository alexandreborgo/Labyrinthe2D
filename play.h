#ifndef HEADER_PLAY
#define HEADER_PLAY

#include "labyrinth.h"

#define TOP 8 // 0000 1000
#define LEFT 1 // 0000 0001 
#define BOTTOM 2 // 0000 0010
#define RIGHT 4 // 0000 0100

int run2(labyrinth* l, tile* t);
int run_try(labyrinth* l, tile* t) ;

#endif