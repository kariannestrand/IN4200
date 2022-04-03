#include "functions.h"

int main(int argc, char const *argv[]){
    bool exercise1 = false;
    bool exercise2 = false;
    bool exercise3 = true;

    if (exercise1){
        if (argc < 2) {
            printf("Usage: ./prog.exe N_ELEMENTS\n");
            return 1;
        }
        int N = atoi(argv[1]);
        double s = 1.5;

        /* defining arrays */
        double *A = malloc(N * sizeof *A);
        double *B = malloc(N * sizeof *B);

        /* initialize B with some random values */
        srand(time(NULL)); // Seeds the random number generator.
        for (size_t i = 0; i < N; i++){
            B[i] = randfrom(0., 2.);
        }

        clock_t start = clock();
        /* making use of the kernel loop */
        for (int i = 0; i < N; i++){
            A[i] = s*B[i];
        }
        clock_t end = clock();

        double total = (double)(end - start)/CLOCKS_PER_SEC;
        int n_bytes = 2 * N * sizeof *A;

        printf("Time: %lfms\n", 1000*total);
        printf("Bytes per sec: %3e\n", n_bytes/total);
        printf("Flops: %3e\n", N/total);

        free(A);
        free(B);
    }

    if (exercise2){
        if (argc < 3) {
            printf("Usage: ./prog.exe N_ELEMENTS\n");
            return 1;
        }
        int N = atoi(argv[1]);
        int stride = atoi(argv[2]);
        double s = 1.5;

        /* defining arrays */
        double *A = malloc(N * sizeof *A);
        double *B = malloc(N * sizeof *B);

        /* initialize B with some random values */
        srand(time(NULL)); // Seeds the random number generator.
        for (size_t i = 0; i < N; i++){
            B[i] = randfrom(0., 2.);
        }

        clock_t start = clock();
        /* making use of the kernel loop */
        for (int i = 0; i < N; i+=stride){
            A[i] = s*B[i];
        }
        clock_t end = clock();

        double total = (double)(end - start)/CLOCKS_PER_SEC;
        int n_bytes = 2 * N * sizeof *A;

        printf("Time: %lfms\n", 1000*total);
        printf("Bytes per sec: %3e\n", n_bytes/total);
        printf("Flops: %3e\n", N/total);

        free(A);
        free(B);


        /*
        Each time a value is fetched from main memory to cache, an entire
        cache line is fetched. If we access all the elements in an array
        one after the other then the cache hit rate is maximal. Every value
        fetched is used. If we introduce a stride, some of the values we
        fetched will not be used. And we will get a cache miss much more often.

        If we have a cache line that can hold $N$ words/doubles, and the
        stride we use is $s$. Then the average cache utilization is given by

        $$\frac{\text{\# words used on average}}{\text{\# words in cache
        line}} = \frac{\frac{N}{s}}{N} = \frac{1}{s} $$

        This gives us the following table, note the last row assumes a cache
        line length of 8 words. When stride is greater than the word length
        of the cache line only one element is used in every line.

        | Stride | Utilization |
        |-------:|------------:|
        |    1   | 100%        |
        |    2   | 50%         |
        |    3   | 33%         |
        |    4   | 25%         |
        |    5   | 20%         |
        |    6   | 17%         |
        |    7   | 14%         |
        |$\geq 8$| 12%         |

        Since the STREAM benchmark we are doing is memory bound we should
        see a severe performance hit due to the frequent cache misses when
        stride increases.
        */
    }

    if (exercise3){
        // a)
        double **A, **B, **C, **D;
        int n, m, p;
        n = 3;
        m = 3;
        p = 5;

        /* allocating arrays */
        alloc2D(&A, n, m);
        alloc2D(&B, m, p);
        alloc2D(&C, n, p);
        alloc2D(&D, n, p);


        /* assign some values */
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < m; j++){
                A[i][j] = i + j + 1;
            }
        }
        for (size_t i = 0; i < m; i++){
            for (size_t j = 0; j < p; j++){
                B[i][j] = i*j + 1;
            }
        }
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < p; j++){
                C[i][j] = 0;
                D[i][j] = 0;
            }
        }

        /* printing A and B */
        printf("A = \n");
        printmat(A, n, m);
        printf("B = \n");
        printmat(B, m, p);

        /* multiplication */
        matmult(A, B, C, n, m, p);
        matmultfast(A, B, D, n, m, p);

        /* printing C and D */
        printf("C = matmult(A, B)\n");
        printmat(C, n, p);
        printf("D = matmultfast(A, B)\n");
        printmat(D, n, p);

        /* freeing memory */
        free2D(A);
        free2D(B);
        free2D(C);
        free2D(D);



        // b)
        /*
        Depending on the size of the matrices different number of loads/stores
        will be done. We denote $M$ as the cache size and $L_C$ as the length
        of a cache line, both in number of words (doubles).

        If the matrices are so small that all the matrices fit in the cache,
        $n\times m + m\times p +n\times p< M$. The first few accesses to
        elements in B will incur a cache miss, but the lines will probably stay
        in the cache for the next iterations. We end up with close to
        $$
        \frac{n\times m + m\times p}{L_C}, \hspace{.5cm} \text{Loads} \\
        \frac{n\times p}{L_C}, \hspace{.5cm} \text{Stores} \\
        $$

        If the matrices are larger we are in a different situation. We access
        the memory in $A$ without strides, so the number of cache line loads
        are $n\times m/L_C$, and $n\times p/L_C$ writes to $C$. For $B$ it's
        a different matter. When one row of $B$ has more elements than fits in
        a cache line then $m\times L_C$ words of the cache is used to store one
        column of $B$, and when $n\times L_C > M$ we incur a cache miss on
        every element of $B$, every time. Since each element of $B$ is used in
        $n$ computations, and there are $m\times p$ elements in $B$ we get
        $n\times m\times p$ cache line loads! The total number of loads and
        stores are
        $$
        \frac{n\times m}{L_C} + n\times m\times p, \hspace{.5cm} \text{Loads}\\
        \frac{n\times p}{L_C}, \hspace{.5cm} \text{Stores}
        $$
        */


        // c)
        /*
        To improve performance we must figure out what the bottleneck is.
        From **b)** we know that we must load an entire cache line for every
        element in B, every time it is used (assuming "large" matrix).
        Increasing the cache hits when accessing elements in B is therefore
        a worthwhile strategy.

        If element `B[k][j]` is at the start of a cache line then `B[k][j+1]`,
        `B[k][j+2]`, `B[k][j+3]` ... `B[k][j+Lc-1]` will be loaded with that
        element. To increase the cache hits we must use these values before
        they are flushed.

        The implementation in the source code unrolls 4 times and should show
        a significant performance increase.

        **Pseudocode:**
        ```
        rest <- p mod 4;
        for i from 0 to n-1:
            for j from 0 to p-rest-1, 4:
                for k from 0 to m-1:
                    C[i,j]   <- C[i,j]   + A[i,k]*B[k,j];
                    C[i,j+1] <- C[i,j+1] + A[i,k]*B[k,j+1];
                    C[i,j+2] <- C[i,j+2] + A[i,k]*B[k,j+2];
                    C[i,j+3] <- C[i,j+3] + A[i,k]*B[k,j+3];
            // The rest:
            for j from p-rest to p-1:
                for k from 0 to m-1:
                    C[i,j]   <- C[i,j]   + A[i,k]*B[k,j];
        ```

        **Note:** We would get maximum cache hits if we unroll the loop with
        the length of the cache line, but that would require to hold $2L_C+1$
        values in registers, an Intel i7 has 16 64 bit (double) registers, and
        $L_C = 8$. If we try to unroll the loop to use the full cache line
        then we would need $17$ registers. But we only have $16$ available.
        The program will deal with this by moving values in and out of
        registers. But at the point where we are using 16 registers we will not
        see the same performance increase. Different CPUs will have a different
        amount of registers.
        */
    }

    return 0;
}
