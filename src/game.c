// game.c
#include "game.h"

void initialize_grid(int *grid, int rows) {
    srand(time(NULL));
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < N; j++) {
            grid[i * N + j] = rand() % 2;
        }
    }
}

void update_grid(int *grid, int *new_grid, int start_row, int end_row, int rank, int size) {
    #pragma omp parallel for collapse(2)
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            int neighbors = 0;
            
            // Count neighbors (handle edge cases)
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;
                    
                    int ni = (i + di + N) % N;
                    int nj = (j + dj + N) % N;
                    
                    neighbors += grid[ni * N + nj];
                }
            }
            
            // Apply Conway's rules
            new_grid[i * N + j] = (neighbors == 3 || (neighbors == 2 && grid[i * N + j])) ? 1 : 0;
        }
    }
}
