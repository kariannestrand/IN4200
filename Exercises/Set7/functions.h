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
#include <float.h>
#include <string.h>
*/

// #define CLOCKS_TO_MILLISEC(t) (t*1000)/CLOCKS_PER_SEC

/* declaration of functions */
void foo(int N, double **mat, double **s, int *v);
void dense_mat_vec(int m, int n, double *x, double *A, double *y);

#endif
