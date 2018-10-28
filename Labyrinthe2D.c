#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

	char choice;
	char input[50];
	int h, l;

	while(1==1) {
    	system("clear");
		printf("Labyrinthe2D\n");
		printf("1. Labyrinthe from file\n");
		printf("2. Ramdom Labyrinthe\n");
		printf("0. Quit\n");

		scanf("%c", &choice);

		if(choice == '0') {
			break;
		}
		
		if(choice == '1' || choice == '2') {
			labyrinthe* lab = allocLabyrinthe();
			
			if(choice == '1') {
				printf("Name of the file to load? ");
				scanf("%s", input);
				initLabyrintheFromFile(lab, input);
			}
			else {
				printf("Size of the labyrinthe?\n");
				printf("Length? ");
				scanf("%d", &h);
				printf("Width? ");
				scanf("%d", &l);
				generateLabyrinthe(lab, h, l);
			}

			if(run2(lab, &(lab->tiles[lab->y_in][lab->x_in])) == 1)
				printf("%s🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂%s", YEL, NRM);
			else
				printf("%s🙁🙁🙁🙁🙁🙁🙁🙁🙁🙁%s", RED, NRM);
			printf("\n");

			if(choice == '2') {
				emptyShittyBuffer();
				printf("Do you want to save this labyrinthe? [y/N] ");
				scanf("%c", input);
	
				if(input[0] == 'y') {
					printf("Name of the file to save the labyrinthe? ");
					scanf("%s", input);
					saveLabyrinthe(lab, input);
				}
			}

			emptyShittyBuffer();
			printf("Press any key to continue...");
			getchar();

			freeLabyrinthe(lab);
		}
	}

	printf("bye\n");

	
	return 0;
}


