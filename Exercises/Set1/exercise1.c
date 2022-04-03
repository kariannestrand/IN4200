
/* exercise 1a */
void ex1a(int N){
    float limit = 4./5.;
    float tolerance = 1e-12;
    float current = 1.0;
    float add = 1.0;
    int i = 1.0;

    while (i++ < N && fabs(current - limit) > tolerance){
        add *= -0.25;
        current += add;
    }

    if (fabs(current - limit) > tolerance){
        printf("failed \n");
    }
    else{
        printf("limit of %f reached after %d iterations \n", current, i);
    }
}

/* exercise 1b */
void ex1b(int N){
    int *rand_array, min, max;                          // rand_array holds adresses to integers
    rand_array = (int *)malloc(N * sizeof(int));        // argument inside malloc-function gives amount of bytes inside array (i. e. N elements of size(int) bytes)

    for (int i = 0; i < N; i++){
        rand_array[i] = rand() % 50;                    // filling with random values up to 50
    }

    min = max = rand_array[0];
    for (int i = 1; i < N; i++){
        min = MIN(min, rand_array[i]);
        max = MAX(max, rand_array[i]);
    }

    printf("Minimum: %d.\nMaximum: %d.\n", min, max);
    free(rand_array);                                   // deallocating the array, frees the block of memory that was assigned to the array so that it can be used for other purposes
}

/* exercise 1c */
void ex1c(int N, int M){
    clock_t start, timer_rowwise, timer_colwise;

    /* first version of allocating a 2D-array to memory */
    double **A;                                       // number of asteriks are dimension of array I think
    A = (double **)malloc(N * sizeof(double *));
    A[0] = (double *)malloc(N * M * sizeof(double));  // this is the actual underlying 1d array of size N * M.
    for (int i = 1; i < N; i++){
        A[i] = &(A[0][M * i]);                        // this line probably requires some unpacking. Just note that A[0][i * M] is the i'th row of the matrix A, and that's what we want A[i] to point to.
        // A[i] = &(A[i-1][M]);                       // this is equivalent but has recursion. Hooray for recursion!
        // A[i] = A[i-1] + M;                         // also equivalent to the above, but uses so-called pointer arithmetic which I just don't like personally.
    }

    /* second version of allocating a 2D-array to memory (this one was way slower for row/column switch) */
    /*
    double **A = (double **)malloc(N * sizeof(double*));
    for(int i = 0; i < N; i++){
        A[i] = (double*)malloc(M * sizeof(double));
    }
    */


    /* first test: Assign values in the usual order */
    start = clock();
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            A[i][j] = N * i + j;
        }
    }
    timer_rowwise = clock() - start;

    /* second test: Assign values in the reverse order */
    start = clock();
    for (int j = 0; j < M; j++){
        for (int i = 0; i < N; i++){
            A[i][j] = N * i + j;
        }
    }
    timer_colwise = clock() - start;


    printf("Time elapsed using i-j-loop: %lu millisec.\n", 1000*timer_rowwise/CLOCKS_PER_SEC);
    printf("Time elapsed using j-i-loop: %lu millisec.\n", 1000*timer_colwise/CLOCKS_PER_SEC);

    /* freeing memory for the first version */
    free(A[0]);
    free(A);


    /* freeing memory for the second version */
    /*
    for (int j = 0 ; j < M; j++){
        free(A[j]);
    }
    free(A);
    */
}


/* exercise 1d */
void ex1d(int Nx, int Ny, int Nz){
    int ***A;
    A = (int ***)malloc(Nz * sizeof(int **));
    A[0] = (int **)malloc(Nz * Ny * sizeof(int *));
    A[0][0] = (int *)malloc(Nz * Ny * Nx * sizeof(int));

    /* first layer of pointers */
    /* the 3d array contains Nz "slices," each of which has Ny columns */
    for (int i = 1; i < Nz; i ++) {
        A[i] = &A[0][Ny * i];
    }

    /* second layer of pointers */
    /* the 3d array contains Ny * Nz rows, each of which has Nx cells */
    for (int j = 1; j < Nz * Ny; j ++) {
        A[0][j] = &A[0][0][j * Nx];
    }

    /* assign some values */
    for (int i = 0; i < Nz; i ++) {
        for (int j = 0; j < Ny; j ++) {
            for (int k = 0; k < Nx; k ++) {
                A[i][j][k] = Nx * Ny * i + Ny * j + k;
                printf("(%d %d %d): %d ", i, j, k, A[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    /* last step */
    free(A[0][0]);
    free(A[0]);
    free(A);

}
