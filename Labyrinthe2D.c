#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "labyrinthe.h"

int main() {
	srand(time(NULL));
	labyrinthe* lab = allocLabyrinthe();
	initLabyrinthe(lab, 10, 10);
	displayLabyrinthe2(lab);
	freeLabyrinthe(lab);
	return 0;
}
