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
double numerical_integration(double x_min, double x_max, int slices);
double pow100(double x);
