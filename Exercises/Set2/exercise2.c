

int ex2a(int argc, char *argv){
    typedef double my_type; // change double to int, short, long etc.

    /*
    supposed to print this if I dont have enough arguments, but for it to work
    it depends on returning 1, so I dont know how to do it with a void-function
    */
    if (argc < 2){
        printf("Usage: ./prog.exe N_ELEMENTS\n");
        return 1;
    }

    int N = atoi(argv);
    printf("Copying %d elements of type double.\n", N);

    /* defining arrays */
    my_type *a = malloc(N * sizeof *a);
    my_type *b = malloc(N * sizeof *a);
    my_type *c = malloc(N * sizeof *a);

    /* initialize a with some values */
    for (size_t i = 0; i < N; i++) {
        a[i] = i;
    }

    clock_t start, start_mcp, end, end_mcp;

    /* copies a to b with normal method */
    start = clock();
    for (size_t i = 0; i < N; i++) {
        b[i] = a[i];
    }
    end = clock();

    /* copies a to c with memcpy */
    start_mcp = clock();
    memcpy(c, a, N * sizeof *a);
    end_mcp = clock();

    double total, total_mcp;
    total = (double)(end - start)/CLOCKS_PER_SEC;
    total_mcp = (double)(end_mcp - start_mcp)/CLOCKS_PER_SEC;

    printf("Time elapsed, for loop: %.2lf ms\n", total*1000);
    printf("Time elapsed, memcpy:   %.2lf ms\n", total_mcp*1000);
    printf("Speedup: %lf\n", total/total_mcp);

    return 0;
}
