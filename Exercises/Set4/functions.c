#include "functions.h"

/*
gives random number between a minimum and maximum, but you could just write
rand() % 100 + 1, which gives random number in the range 1 to 100??
*/
double randfrom(double min, double max){
    /*
    I guess this function allows you to set min and max of rand(), cause
    otherwise I dont see why you couldnt just use rand()
    */
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


/* allocates 2D-array */
int alloc2D(double ***A, int n, int m){
    *A = malloc(n * sizeof *A);
    (*A)[0] = malloc(n * m * sizeof (*A)[0]);

    /*
    || means OR, but I dont understand ! because there is no argument, like
    if c = 5 then !(c == 5) returns 0 since its true (1 when false))
    */
    if (!(*A)[0] || !*A){
        printf("Allocation failed\n");
        return 1;
    }

    for (size_t i = 1; i < n; i++){
        (*A)[i] = &((*A)[0][i * m]);
    }
    return 0;
}


/* frees 2D-array */
int free2D(double **A){
    free(A[0]);
    free(A);

    return 0;
}

/* matrix-matrix multiplication, C = A*B, assumes zero initialized C */
int matmult(double **A, double **B, double **C, int n, int m, int p){
    for (size_t i = 0; i < n; i++){             // first dim in C.
        for (size_t j = 0; j < p; j++){         // second dim in C.
            for (size_t k = 0; k < m; k++){     // inner dim in A and B.
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return 0;
}


/*
fast version of matrix-matrix multiplication, C = A*B, assumes
zero initialized C
*/
int matmultfast(double **A, double **B, double **C, int n, int m, int p){
    int rest = p%4;
    for (size_t i = 0; i < n; i++){
        for (size_t j = 0; j < p-rest; j+=4){   // stride by 4
            for (size_t k = 0; k < m; k++){     // inner dim in A and B
                C[i][j]   += A[i][k]*B[k][j];
                C[i][j+1] += A[i][k]*B[k][j+1];
                C[i][j+2] += A[i][k]*B[k][j+2];
                C[i][j+3] += A[i][k]*B[k][j+3];
            }
            /* rest loop */
            for (size_t j = p-rest; j < p; j++){
                for (size_t k = 0; k < m; k++){
                    C[i][j] += A[i][k]*B[k][j];
                }
            }
        }
    }

    return 0;
}


/* prints matrix */
int printmat(double **A, int n, int m){
    for (size_t i = 0; i < n; ++i){
        printf("| ");
        for (size_t j = 0; j < m; ++j){
            printf("%4.0lf ", A[i][j]);
        }
        printf("|\n");
    }
    return 0;
}
