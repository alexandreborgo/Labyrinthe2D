#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "labyrinthe.h"
#include "play.h"

#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"

 // 😐😕🙁😟😠😡

int main() {
	srand(time(NULL));

	labyrinthe* lab = allocLabyrinthe();
	generateLabyrinthe(lab, 10, 10);

	int i;
	if(run2(lab, &(lab->tiles[lab->y_in][lab->x_in])) == 1)
		printf("%s🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂", YEL);
	else
		printf("%s🙁🙁🙁🙁🙁🙁🙁🙁🙁🙁", RED);
	printf("\n");

	freeLabyrinthe(lab);
	
	return 0;
}


