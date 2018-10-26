all: do clean

tile.o: tile.c tile.h
	gcc -c tile.c

labyrinthe.o: labyrinthe.c labyrinthe.h tile.h
	gcc -c labyrinthe.c

Labyrinthe2D.o: Labyrinthe2D.c labyrinthe.h
	gcc -c Labyrinthe2D.c

do: tile.o labyrinthe.o Labyrinthe2D.o
	gcc -o Labyrinthe2D Labyrinthe2D.o labyrinthe.o tile.o

clean: 
	rm *.o
