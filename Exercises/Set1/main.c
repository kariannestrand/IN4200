#include "main.h"
#include "exercise1.c"
#include "exercise2.c"
#include "exercise3.c"


int main(int argc, char *argv[]){
    bool exercise1a = false;
    bool exercise1b = false;
    bool exercise1c = false;
    bool exercise1d = false;
    bool exercise2a = false;
    bool exercise2b = false;
    bool exercise3a = true;

    /* exercise 1a */
    if (exercise1a){
        int N = 30;
        ex1a(N);
    }

    /* exercise 1b */
    if (exercise1b){
        int N = 30;
        ex1b(N);
    }

    /* exercise 1c */
    if (exercise1c){
        int N, M = 10000;
        ex1c(N, M);
    }

    /* exercise 1d */
    if (exercise1d){
        int Nx, Ny, Nz = 3;
        ex1d(Nx, Ny, Nz);
    }

    /* exercise 2a */
    if (exercise2a){
        ex2a();
    }

    /* exercise 2b */
    if (exercise2b){
        int n = 3;
        int m = 4;
        double c = 2.0;
        ex2b(n, m, c);
    }

    /* exercise 3a */
    if (exercise3a){
        int unsorted[20];
        int perm[20];

        for (int i = 0; i < 20; i ++){
            unsorted[19 - i] = i;
            perm[i] = i;
        }

        sort_perm(unsorted, perm, 0, 20);
        for (int i = 0; i < 20; i ++) printf("%d\n", unsorted[perm[i]]);
    }

    return 0;
}
