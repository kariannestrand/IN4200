#include "functions.h"

// WORKLOAD IS ONLY CALLED IN PARALLEL
/* workload
 * - struct Matrix *mesh: pointer to struct of type Matrix holding
 *                        a theoretical matrix for compuation purposes.
 * - int x: an iteration value, used to find the identity of the thread
 *          in both dimension x (used by M and S) and y (used by N and T).
 */
int workload(struct Matrix *mesh, int x){
    int i = x / mesh->S;
    int j = x % mesh->T;

    // S_i x T_j
    int k, l;
    // k and l are the size of the grid this specific thread is to work on

    k = (mesh->M / mesh->S) + ((i < (mesh->M % mesh->S)) ? 1 : 0);
    l = (mesh->N / mesh->T) + ((j < (mesh->N % mesh->T)) ? 1 : 0);

    /* The above lines are synonymous with the below example:
    * > k = (mesh->M / mesh->S);
    * > if (i < (mesh->M % mesh->S)) k++;
    */



    // Where to start our workload:
    int k_sta, l_sta;

    // naive assumption of starting coordinates
    k_sta = (mesh->M / mesh->S) * i;
    l_sta = (mesh->N / mesh->T) * j;

    k_sta+= i<(mesh->M % mesh->S) ? i : (mesh->M % mesh->S);
    l_sta+= j<(mesh->N % mesh->T) ? j : (mesh->N % mesh->T);

    // Have thread identify itself, and the size region it is working on, and where said region starts
    printf("Thread[%d, %d] reporting for duty at [%d, %d] with size %d x %d\n", i, j, k_sta, l_sta, k, l);

    /* WORKLOAD */

  return 0;
}
