#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <dirent.h>
#include <string.h>

#include "labyrinth.h"
#include "play.h"

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"

void emptyShittyBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
}

void play(labyrinth* lab) {
	if(run2(lab, &(lab->tiles[lab->y_in][lab->x_in])) == 1)
		printf("%s🙂🙂🙂🙂🙂🙂🙂🙂🙂🙂%s", YEL, NRM);
	else
		printf("%s🙁🙁🙁🙁🙁🙁🙁🙁🙁🙁%s", RED, NRM);
	printf("\n");
}

int menu(int x, int y, char list[x][y], char* message) {
	WINDOW *w;
	int i;
	int c;
	char item[30];
	initscr();
	clear();
	w = newwin( 2+x, 30, 2, 0);
	box( w, 0, 0 );
	
	mvprintw(1, 0, "%s", message);
	for( i=0; i<x; i++ ) {
		if( i == 0 )
			wattron( w, A_STANDOUT );
		else
			wattroff( w, A_STANDOUT );
		sprintf(item, "%-7s",  list[i]);
		mvwprintw( w, i+1, 2, "%s", item );
	}
	
	refresh();

	i = 0;
	noecho(); 
	keypad( w, TRUE );
	curs_set( 0 );

	while(( c = wgetch(w)) != '\n') {
		sprintf(item, "%-7s",  list[i]);
		mvwprintw( w, i+1, 2, "%s", item ); 
		
		switch( c ) {
			case KEY_UP:
				i--;
				i = ( i<0 ) ? x-1 : i;
				break;
			case KEY_DOWN:
				i++;
				i = ( i>x-1 ) ? 0 : i;
				break;
		}

		wattron( w, A_STANDOUT );
			
		sprintf(item, "%-7s",  list[i]);
		mvwprintw( w, i+1, 2, "%s", item);
		wattroff( w, A_STANDOUT );
	}

	delwin( w );
	endwin();

	return i;
}

int main() {
	srand(time(NULL));

	char input[50];
	int h, l;

	
	char menu_options[3][26] = { "Labyrinth from file", "Generate ramdom Labyrinth", "Exit" };
	int i = 0, width = 26;

	while(1==1) {

		system("clear");

		i = menu(3, 26, menu_options, "Labyrinth2D");
		
		if(i == 2) {
			break;
		}

		labyrinth* lab = allocLabyrinth();

		if(i == 0) {

			DIR *d;
			struct dirent *dir;
			char files_options[50][50];
			int index = 0;
			d = opendir("labyrinths");
			if (d) {
				while ((dir = readdir(d)) != NULL) {
					if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..")) {
						sprintf(files_options[index++], "labyrinths/%s", dir->d_name);
					}
				}
				closedir(d);
			}
			sprintf(files_options[index++], "Return");
			int last = index-1;
			index = menu(index, 50, files_options, "Name of the file to load the labyrinth? Labyrinth files should be placed in the sub folder labyrinths.");

			if(index == last) {
				continue;
			}

			if(access(files_options[index], F_OK ) != 0) {
				printf("Can't open file '%s' (check name or permissions).\n", files_options[index]);
				printf("Press any key to return to the menu...");
				getchar();
				continue;
			}
			printf("Loading labyrinth from file %s...\n", files_options[index]);
			int errors = initLabyrinthFromFile(lab, files_options[index]);

			if(errors != 0) {
				printf("This labyrinth is poorly formed (%d errors). Do you still want to load it? [y/n] ", errors);
				scanf("%c", input);
				getchar();

				if(input[0] != 'y') {
					continue;
				}
				
			}
			play(lab);

			
			printf("Press any key to return to the menu...");
			getchar();
		}
		else if(i == 1) {			

			printf("Size of the labyrinth? Minimum size: (2,2)\n");
			struct winsize w;
    		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			printf("With your current terminal size maximum labyrinth size that can be display is (%d,%d)\n", w.ws_row/2-1, w.ws_col/6);

			do {
				printf("Length? ");
				scanf("%d", &h);
			} while(h < 2);
			do {
				printf("Width? ");
				scanf("%d", &l);
			} while(l < 2);
			getchar();
			generateLabyrinth(lab, h, l);

			play(lab);
			
			printf("Do you want to save this labyrinth? [y/n] ");
			scanf("%c", input);

			if(input[0] == 'y') {
				printf("Name of the file to save the labyrinth? ");
				scanf("%s", input);
				saveLabyrinth(lab, input);
			}
		}

		freeLabyrinth(lab);
	}

	printf("bye %s🙂%s\n", YEL, NRM);

	return 0;
}


