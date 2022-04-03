#include "functions.h"

int main(int argc, char const *argv[]){
    bool exercise1 = false;
    bool exercise2 = false;
    bool exercise3 = true;

    if (exercise1){
        /*
        We define code balance as the data traffic in words divided by the
        number of floating point operations.
        $$B_c = \frac{\text{Words}}{\text{Flops}}$$
        */

        // a) dense matrix-vector multiplication:
        /*
        for (j = 0; j < N; j++){
            for (i = 0; i < N; i++){
                y[j] += A[j][i]*B[i];
            }
        }

        For each iteration we have two floating point operations. There are a
        total of $N^2$ iterations for a total of $2N^2$ flop.
        Depending on the size of $N$ and the cache size we have two scenarios.
        Assuming that $N$ is large and that `B` does not fit
        in cache we end up loading the elements in `B` every single iteration
        of the `j` loop, $N$ elements loaded $N$ times. `A` is accessed
        without strides and therefore is loaded once, $N^2$ elements.
        `y[j]` Can stay in the register for the entire inner loop and is
        negligible (for large $N$).

        $$ B_c = \frac{2N^2}{2N^2} = 1 $$
        */


        // b) vector norm
        /*
        double s = 0.;
        for (i = 0; i < N; i++){
            s += A[i]*A[i];
        }

        `s` stays in a register for the entire loop and is negligible.
        We load `A` without strides which gives a total of $N$ loads.
        For every iteration there are two flop though.
        $$B_c = \frac{N}{2N} = \frac{1}{2}$$
        */


        // c) scalar product
        /*
        double s = 0.;
        for (i = 0; i < N; i++){
            s += A[i]*B[i];
        }

        Same as b) but we need to load `B` as well.
        $$B_c = \frac{2N}{2N} = 1$$
        */


        // d) scalar product with indirect access
        /*
        double s = 0.;
        for (i = 0; i < N; i++){
            s += A[i]*B[K[i]];
        }

        This one is a bit tricky. To constrain the problem a bit I'm going to
        say that a double is 8 bytes and that an int is 4 bytes.
        Just counting the loads, without thinking about cache lines.
        We have two loads for `A` and `B`, and half a load for `K`
        (size of int is 1/2 that of a double).
        This gives us a code balance of
        $$B_c = \frac{2.5}{2} = 1.25$$
        This balance turns out to be true for the case when the integers
        in `K` are all sequential, $0, 1, \dots, N-1$. But for an array of
        random integers this is not likely.
        To illustrate the differences in code balance we can end up with
        we will look at two more cases.

        `K[i]` Constant:
        If all the elements in `K` are the same element (or all point to
        the same cache line). Then we get the best case scenario, we still
        have $N$ loads for `A` and $N/2$ loads for `K`, but the loads for `B`
        are negligible.
        $$B_c = \frac{N + N/2}{2N} = 0.75$$
        This is the best case scenario with fewest loads.

        `K[i]` Random, always in strides of more than $L_C$:
        If we again assume that `B` does not fit in cache, and that `K[i]`
        is strided in a "maximally bad" way. Then we can imagine that each
        time we load an elements of `B` we must load the entire cache line
        that element is on. That is 8 loads for each element in `B`. Adding
        this to the one load for `A` and half a load for `K` we get
        $$B_c = \frac{N + N/2 + 8N}{2N} = 4.75$$
        */
    }

    if (exercise2){
        /* declearing arrays */
        double **A;
        double *B, *y;
        int N = 3;

        /* allocating arrays */
        alloc2D(&A, N, N);                  // 2D
        B = malloc(N * sizeof(double));     // 1D
        y = malloc(N * sizeof(double));     // 1D


        /*
        apply unroll and jam, with 4 as the unroll depth, to the outer loop
        of the following code
        */
        for (int j = 0; j < N; j++){
            for (int i = 0; i <= j; i++){
                y[j] += A[j][i]*B[i];
            }
        }
        /*
        This is a matrix vector multiplication with a lower triangular matrix.
        And it's that lover triangular bit that gives rise to the complexity.
        We are going go through $j$ in strides of 4, so we will get a remainder
        for every $N$ not divisible by 4. Calculating the remainder, and
        running through the first few rows of `A` in the regular way we can
        then focus on the remaining `N - remainder` rows that are divisible by 4.

        **Note:** Any reason to do the remainder rows first? Hint: how many
        branches are there in the first `remainder` iterations of `j` vs the
        last `remainder`.

        Unrolling `j` four-way is rather easy now that we
        know `(N - remainder)%4 = 0`.
        */
        int remainder = N % 4;
        for (size_t j = 0; j < remainder; j++){
            for (size_t i = 0; i <= j; i++){
                y[j] += A[j][i]*B[i];
            }
        }
        for (size_t j = remainder; j < N; j+=4){
            for (size_t i = 0; i <= j; i++){
                y[j]   += A[j][i]   * B[i];
                y[j+1] += A[j+1][i] * B[i];
                y[j+2] += A[j+2][i] * B[i];
                y[j+3] += A[j+3][i] * B[i];
            }
        }
        /*
        This solution does not cover all the values though. If we inspect the
        loop, we see that we are missing several values for each iteration
        of `j`. Six to be exact. E.g. when `j` is 2, we set values in `y`
        for $j = 2, 3, 4,$ and $5$, but $i$ is never incremented above 2.
        In the next iteration of the outer loop $j = 6, 7, 8,$ and $9$, and we
        never catch these values. To solve this we add the remaining values
        outside the inner loop, but still inside the outer one.
        */
        for (size_t j = 0; j < remainder; j++){
            for (size_t i = 0; i <=  j; i++){
                y[j] += A[j][i]*B[i];
            }
        }
        for (size_t j = remainder; j < N; j+=4){
            for (size_t i = 0; i <= j; i++){
                y[j]   += A[j][i] * B[i];
                y[j+1] += A[j+1][i]*B[i];
                y[j+2] += A[j+2][i]*B[i];
                y[j+3] += A[j+3][i]*B[i];
            }
            // These values are not included in the unrolled loop.
            y[j+1] += A[j+1][j+1]*B[j+1];
            y[j+2] += A[j+2][j+1]*B[j+1];
            y[j+2] += A[j+2][j+2]*B[j+2];
            y[j+3] += A[j+3][j+1]*B[j+1];
            y[j+3] += A[j+3][j+2]*B[j+2];
            y[j+3] += A[j+3][j+3]*B[j+3];
        }

        /* freeing memory */
        free2D(A);
        free(B);
        free(y);
    }

    if (exercise3){
        /*
        optimize foo(), assume it will be repeatedly called, with changing
        contents of the input arrays s and v
        */

        /* declearing arrays */
        double **mat, **s;
        int *v;
        int N = 3;

        /* allocating arrays */
        alloc2D(&mat, N, N);            // 2D
        alloc2D(&s, N, N);              // 2D
        v = malloc(N * sizeof(int));    // 1D


        /* runs foo-function */
        foo(N, mat, s, v);

        /* freeing memory */
        free2D(mat);
        free2D(s);
        free(v);


    }
}
