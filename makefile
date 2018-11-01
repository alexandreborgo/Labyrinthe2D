all: do clean

play.o: play.c play.h
	gcc -c play.c

tile.o: tile.c tile.h
	gcc -c tile.c

labyrinth.o: labyrinth.c labyrinth.h tile.h
	gcc -c labyrinth.c

Labyrinth2D.o: Labyrinth2D.c labyrinth.h
	gcc -c Labyrinth2D.c

do: tile.o labyrinth.o Labyrinth2D.o play.o
	gcc -o Labyrinth2D Labyrinth2D.o labyrinth.o tile.o play.o -lncurses

clean: 
	rm *.o
