#include "functions.h"


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


/* optimized foo-function */
void foo(int N, double **mat, double **s, int *v){
    // original code snippet to be optimized:
    /*
    double val;
    for (int j = 0; j < N; j++){
        for (int i = 0; i < N; i++){
            val = 1.0*(v[j]%256);
            mat[i][j] = s[i][j]*(sin(val)*sin(val) - cos(val)*cos(val));
        }
    }
    */


    /*
    In this code snippet there are some obvious things we can do with minimal
    effort, even before profiling the code. One god principle for efficient
    code is to simply do less stuff.

    Using
    $$
    \cos(\alpha \pm \beta) = \cos(\alpha)\cos(\beta) \mp \sin(\alpha)\sin(\beta)
    $$
    to rewrite
    $$
    \sin(\text{val})\sin(\text{val}) - \cos(\text{val})\cos(\text{val})
    = -\cos(2\text{val})
    $$
    we reduce the number of operations without any sacrifice. Combining this
    with `val` we have simplified quite a bit already. Since val only depends
    on `j` we can move it outside the inner loop as well, such that the code
    snippet becomes

    double *val = ;
    for (int j = 0; j < N; j++){
        val = -cos(2.0*(v[j]%256));
        for (i=0; i<N; i++) {
          mat[i][j] = s[i][j] * val;
        }
    }

    Now we are stuck with strided memory access in `mat` and `s`. If we switch
    the indexes we will be forced to put the calculation of `val` back inside
    the inner loop. To avoid this we can instead tabulate the different values
    `val` can take and then only index it inside the inner loop. To get the
    correct values we need to go via `v`. But then we end up doing $N^2$ modulo
    operations again. To avoid this we can tabulate `v[i]%256` as well. Note
    that $\cos(-x) = \cos(x)$, so we can map the negative values from the
    modulo operation to the positive ones.
    */

    double *val = malloc(256 * sizeof *val);
    int *vtab = malloc(N * sizeof *vtab);
    for (int i = 0; i < 256; i++){
        val[i] = -cos(2.0*i);
    }
    for (size_t i = 0; i < N; i++){
        vtab[i] = abs(v[i]%256);
    }
    for (int j = 0; j < N; j++){
        for (int i = 0; i < N; i++){
            mat[j][i] = s[j][i]*val[vtab[i]];
        }
    }
    free(val);
    free(vtab);

    /*
    **Note:** The table over the cos values should be computed once outside
    the scope of the function if it's called repeatedly.
    */
}
