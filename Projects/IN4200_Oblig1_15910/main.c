#include "main.h"

int main(int argc, char *argv[]){
    if (argc < 5) {
        printf("Usage: ./prog.exe filename d epsilon n \n");
        return 1;
    }


    /* command line arguments */
    char *filename = argv[1];        // filename of the web graph file
    double d = atof(argv[2]);        // damping constant
    double epsilon = atof(argv[3]);  // convergence threshold value
    double n = atof(argv[4]);        // number of top webpages being printed


    /* declearation of variables */
    int N;                           // total number of webpages
    int *row_ptr;                    // row pointers
    int *col_idx;                    // column indices
    double *val;                     // non-zero values
    double *scores = malloc(N * sizeof *scores);

    /* calling methods */
    read_graph_from_file(filename, &N, &row_ptr, &col_idx, &val);
    if (n > N){
        printf("\n");
        printf("warning: number of top webpages being printed is larger than total number of webpages (%d) \n", N);
        exit(0);
    }
    PageRank_iterations(N, row_ptr, col_idx, val, d, epsilon, scores);
    top_n_webpages(N, scores, n);


    /* freeing memory of allocated arrays */
    free(row_ptr);
    free(col_idx);
    free(val);
}
