#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define CLOCKS_TO_MILLISEC(t) (t*1000)/CLOCKS_PER_SEC 

/* declaration of functions */
void initialise(double *arr, int len);
void ex1a();
int ex2a(int argc, char *argv);
void ex3a(int nx, int ny, int nz);
