// main.c
#include "game.h"
#include <sys/time.h>

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char **argv) {
    int rank, size;
    double start_time, end_time;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Calculate local grid size
    int rows_per_proc = N / size;
    int start_row = rank * rows_per_proc;
    int end_row = start_row + rows_per_proc;
    
    // Allocate memory for local grids
    int *grid = (int *)calloc(N * N, sizeof(int));
    int *new_grid = (int *)calloc(N * N, sizeof(int));
    
    // Initialize grid on rank 0
    if (rank == 0) {
        initialize_grid(grid, N);
    }
    
    // Broadcast initial grid to all processes
    MPI_Bcast(grid, N * N, MPI_INT, 0, MPI_COMM_WORLD);
    
    // Start timing
    start_time = get_time();
    
    // Main game loop
    for (int iter = 0; iter < ITERATIONS; iter++) {
        update_grid(grid, new_grid, start_row, end_row, rank, size);
        
        // Gather all parts back to rank 0
        MPI_Allgather(&new_grid[start_row * N], rows_per_proc * N, MPI_INT,
                      grid, rows_per_proc * N, MPI_INT, MPI_COMM_WORLD);
    }
    
    // End timing
    end_time = get_time();
    
    if (rank == 0) {
        printf("Time taken: %f seconds\n", end_time - start_time);
    }
    
    // Cleanup
    free(grid);
    free(new_grid);
    MPI_Finalize();
    return 0;
}
