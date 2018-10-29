#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "labyrinthe.h"
#include "play.h"

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"

 // 😐😕🙁😟😠😡

void emptyShittyBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
	srand(time(NULL));

	char choice[10];
	char input[50];
	int h, l;

	while(1==1) {
    	system("clear");
		printf("Labyrinthe2D\n\n");
		printf("1. Labyrinthe from file\n");
		printf("2. Ramdom Labyrinthe\n");
		printf("0. Quit\n");

		scanf("%s", choice);

		if(*choice == '0') {
			break;
		}		
		else if(*choice == '1') {
			labyrinthe* lab = allocLabyrinthe();

			printf("Name of the file to load? ");
			scanf("%s", input);
			if(access(input, F_OK ) != 0) {
				printf("Can't open file '%s' (check name or permissions).\n", input);
				emptyShittyBuffer();
				printf("Press any key to continue...");
				getchar();
				continue;
			}
			initLabyrintheFromFile(lab, input);
			

			if(run2(lab, &(lab->tiles[lab->y_in][lab->x_in])) == 1)
				printf("%s🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂%s", YEL, NRM);
			else
				printf("%s🙁🙁🙁🙁🙁🙁🙁🙁🙁🙁%s", RED, NRM);
			printf("\n");

			emptyShittyBuffer();
			printf("Press any key to continue...");
			getchar();

			freeLabyrinthe(lab);
		}
		else if(*choice == '2') {
			labyrinthe* lab = allocLabyrinthe();

			printf("Size of the labyrinthe? Minimum size: (2,2)\n");
			do {
				printf("Length? ");
				scanf("%d", &h);
			} while(h < 2);
			do {
				printf("Width? ");
				scanf("%d", &l);
			} while(l < 2);
			generateLabyrinthe(lab, h, l);

			emptyShittyBuffer();
			printf("Do you want to save this labyrinthe? [y/n] ");
			scanf("%c", input);

			if(input[0] == 'y') {
				printf("Name of the file to save the labyrinthe? ");
				scanf("%s", input);
				saveLabyrinthe(lab, input);
			}

			freeLabyrinthe(lab);
		}
	}

	printf("bye 🙂\n");

	return 0;
}


