#ifndef FUNCTIONS_
#define FUNCTIONS_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <mpi.h>
#include <omp.h>

typedef int numeric;

/* declaration of functions */
int compare_exchange(numeric *a, numeric *b);
int oddeven(numeric *a, int n);
int oddeven_anylenght(numeric *a, int n);
int oddeven_stop(numeric *a, int n);
int oddeven_omp(numeric *a, int n);
int printvec(numeric *a, int n);

#endif
