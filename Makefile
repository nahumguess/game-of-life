// Makefile
CC=mpicc
CFLAGS=-O3 -fopenmp -Wall
LIBS=-lm

all: game

game: main.c game.c
	$(CC) $(CFLAGS) main.c game.c -o game $(LIBS)

clean:
	rm -f game *.o
