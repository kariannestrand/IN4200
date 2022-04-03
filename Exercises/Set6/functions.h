#ifndef FUNCTIONS_
#define FUNCTIONS_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <mpi.h>
#include <omp.h>


/*
Suppose there is a 2D rectangular uniform mesh, which has M points in the
x-direction and N points in the y-direction. Please describe in detail how to
carry out a checkerboard block decomposition of the mesh into S ×T blocks,
as evenly as possible. Note that M may not be divisible by S, and N may
not be divisible by T
*/

/* Struct Matrix
 * The Matrix struct is an example of a possible mesh,
 * containing the variables necessary to define its dimensions (M, N);
 *
 * S, T are technically used for parallelization purposes.
 */
struct Matrix{
    int M, N;       // matrix dimensions
    int S, T;       // multiproc grid
    float * data;   // M * N
};

/* declaration of functions */
int workload(struct Matrix *mesh, int x);

#endif
