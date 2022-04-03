#ifndef FUNCTIONS_
#define FUNCTIONS_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

/*
#include <float.h>
#include <string.h>
*/

// #define CLOCKS_TO_MILLISEC(t) (t*1000)/CLOCKS_PER_SEC

/* declaration of functions */
int alloc2D(double ***A, int n, int m);
int free2D(double **A);
void foo(int N, double **mat, double **s, int *v);

#endif
