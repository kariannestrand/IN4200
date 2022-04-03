#include "main.h"
#include "exercise1.c"
#include "exercise2.c"
#include "exercise3.c"


int main(int argc, char *argv[]){
    bool exercise1a = false;
    bool exercise2a = false;
    bool exercise3a = true;

    if (exercise1a){
        ex1a();
    }

    if (exercise2a){
        ex2a(argc, argv[1]);
    }

    if (exercise3a){
        int nx = 10;
        int ny = 4;
        int nz = 5;
        ex3a(nx, ny, nz);
    }

    return 0;
}
