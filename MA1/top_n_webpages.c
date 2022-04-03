#include "main.h"


/*
 *  function:  top_n_webpages
 * --------------------
 *  prints out the top n webpages with both their PageRank scores and
 *  webpage indices
 *
 *  N: the total number of webpages
 *  scores: 1D array with the converged PageRank scores
 *  n: number of webpages being printed
 */
void top_n_webpages(int N, double *scores, int n){
    int *webpage = malloc(N * sizeof *webpage); // array to store webpage numbers
    int i, j, idx;
    double x, tmp;

    printf("\n");
    printf("The top %d webpages of the calculated PageRank scores: \n", n);
    printf("webpage index:       scores: \n");


    for (i = 0; i < N; i++){
        webpage[i] = i;    // filling webpage numbers in ascending order
    }

    double start = omp_get_wtime();
    #pragma omp parallel private(i, idx)
    {
    for (i = 0; i < n; i++){
        idx = i;

        // ordering scores in descending order and finding respective indices
        #pragma omp for
        for (j = i + 1; j < N; j++){
            if (scores[j] > scores[i]){
                idx = j;

                tmp = scores[i];
                scores[i] = scores[idx];
                scores[idx] = tmp;
                swap(&webpage[i], &webpage[idx]);
            }
        }
        printf("%d                    %f \n", webpage[i], scores[i]);
    }
    }

    double end = omp_get_wtime();
    double tot = end - start; // Total serial time.
    printf("\n");
    printf("Time no omp:  %lf\n", tot);

    free(webpage);
}
