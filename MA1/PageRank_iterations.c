#include "main.h"


/*
 *  function:  PageRank_iterations
 * --------------------
 *  implements the iterative procedure of the PageRank algorithm
 *
 *  N: the total number of webpages
 *  row_ptr: 1D array with the indices at which new rows start in val
 *  col_idx: 1D array with the column index of each non-zero in val
 *  val: 1D array with all non-zeros of the hyperlink matrix
 *  d: damping constant
 *  epsilon: convergence threshold value
 *  scores: pre-allocated 1D array which is stored with the computed PageRank
 *          scores inside the function
 */
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores){
    /* declearation of variables */
    double *x = malloc(N * sizeof *x);              // array to store calculated scores
    int *dangling = malloc(N * sizeof *dangling);   // array to find dangling webpages
    int *temporary = malloc(N * sizeof *temporary); // temporary array to find dangling webpages
    double W;                                       // dangling scalar
    double *tmp, temp;                              // temporary variables
    double diff = 1.;                               // initial difference between calculated scores
    int k = 0, l = 0;                               // counters
    int i, j;


    /* finding dangling wepages */
    // finding at which columns there exists non-zeros:
    #pragma omp parallel for
    for (i = 0; i < row_ptr[N]; i++){    // row_ptr[N] = number of non-zeros i. e. edges
        temporary[col_idx[i]] = 1.;      // dangling is set to 1 at each column there exists a non-zero
    }
    // counting the number of columns where non-zeros do not exist:
    // iterations depend on each other, parallelization is not possible
    for (i = 0; i < N; i++){
        if (temporary[i] != 1.){
            dangling[k] = i;
            k++;
        }
    }
    printf("\n");
    printf("Number of dangling webpages: %d \n", k);



    /* PageRank algorithm */
    #pragma omp parallel for
    for (i = 0; i < N; i++){
        scores[i] = 1. / N;             // initial guess
    }

    double pre_cal_1 = (1. - d) / N;    // pre calculation of first terms

    #pragma omp parallel
    {
    while (diff >= epsilon){

        #pragma omp barrier
        #pragma omp master
        {
        diff = 0.;        // resets difference
        W = 0.;           // resets dangling factor
        }

        l++;

        #pragma omp for reduction(+:W)
        for (i = 0; i < k; i++){
            W += scores[dangling[i]];           // summation of PageRank scores
        }

        double pre_cal_2 = d * W / N;           // pre calculation of second term
        double pre_cal = pre_cal_1 + pre_cal_2; // total pre calculation

        #pragma omp for private(j, temp) reduction(max: diff)
        for (i = 0; i < N; i++){
            x[i] = 0;  // initialize each score with zero between calculations of each element

            for (j = row_ptr[i]; j < row_ptr[i+1]; j++){
                // sparse matrix-vector multiplication with CRS format:
                x[i] += d * val[j] * scores[col_idx[j]];
            }
            x[i] += pre_cal;

            temp = fabs(x[i] - scores[i]);  // temporary difference between calculated scores
            if (temp > diff){
                diff = temp;                // diff becomes largest difference
            }
        }
        // swap so that previous scores are used in the next iteration:
        #pragma omp master
        {
        tmp = x;
        x = scores;
        scores = tmp;
        }
    }
    }


    // printing result of convergence:
    printf("\n");
    printf("After %d iterations PageRank scores converge to: \n", l);
    for (i = 0; i < N; i++){
        printf("%f \n", scores[i]);
    }



    /* freeing memory of allocated arrays */
    free(dangling);
    free(x);
}
