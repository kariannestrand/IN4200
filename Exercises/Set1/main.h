#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

typedef struct{
    int n;
    char *times;
    double *temps;
}temperature_data;

/* this is for exercise 1b */
/*
(The bit with the question mark and the colon and the other stuff is a fancy if-else shorthand which you hopefully recognize from JAVA.)
https://stackoverflow.com/questions/19846570/macros-c-programming-define-mina-b-a-b-a-b
*/
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MINIDX(oldidx, i, arr) (((arr[oldidx]) < (arr[i]))?(oldidx):(i))
#define MAXIDX(oldidx, i, arr) (((arr[oldidx]) > (arr[i]))?(oldidx):(i))


/* declaration of functions */
void ex1a(int N);
void ex1b(int N);
void ex1c(int N, int M);
void ex1d(int Nx, int Ny, int Nz);
void ex2a();
void ex2b(int n, int m, double c);
void swap();
void sort();
