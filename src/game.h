// game.h
#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#ifdef _OPENMP
#include <omp.h>
#endif

// Size of the grid
#define N 1024
#define ITERATIONS 1000

// Function declarations
void initialize_grid(int *grid, int rows);
void update_grid(int *grid, int *new_grid, int start_row, int end_row, int rank, int size);
void print_grid(int *grid, int rows);

#endif
