/*
When making a "function" like this via define, wherever it is invoked the
compiler simply replaces the function call with the code. That's why the m,n and
o arguments aren't necessary, because they exist wherever idx is invoked.
Since a conventional function call is slightly time-consuming, defining the
index in this way should be somewhat faster than making a proper index function,
at least when it's called over and over like here.
*/
#define idx(i, j, k) ny*nx*i + nx*j + k

void ex3a(int nx, int ny, int nz){

    /* first 3D array, v, uninitialized (malloc) */
    double ***v = (double ***)malloc(nx * sizeof(double **));
    v[0] = (double **)malloc(nx * ny * sizeof(double *));
    v[0][0] = (double *)malloc(nx * ny * nz * sizeof(double));
    for (int i = 1; i < nx; i++){
        v[i] = &v[0][ny * i];
    }
    for (int j = 1; j < nx * ny; j++){
        v[0][j] = &v[0][0][j * nx];
    }

    /* second 3D array, u, initialized with zeros (calloc) */
    double ***u = (double ***)calloc(nx, sizeof(double **));
    u[0] = (double **)calloc(nx * ny, sizeof(double *));
    u[0][0] = (double *)calloc(nx * ny * nz, sizeof(double));
    for (int i = 1; i < nx; i++){
        u[i] = &u[0][ny * i];
    }
    for (int j = 1; j < nx * ny; j++){
        u[0][j] = &u[0][0][j * nx];
    }


    /* assign the values to v */
    double denom = (nx-1) * (ny-1) * (nz-1);  // use your homan intelligence
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k ++){
                v[i][j][k] = 2.0 + sin((i * j * k * M_PI)/denom);
                printf("v[%d][%d][%d]: %f ", i, j, k, v[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }


    /* update u */
    for (int i = 1; i < nx-2; i++){
        for (int j = 1; j < ny-2; j++){
            for (int k = 1; k < nz-2; k ++){
                u[i][j][k] = v[i][j][k] + (v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] - 6.0 * v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1])/6.0;
                // memcpy(v[i][j][k], u[i][j][k], sizeof *v); // copying u to v before each iteration ?? this does not work idk
                printf("u[%d][%d][%d]: %f ", i, j, k, u[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    /* deallocating v and u */
    free(v[0][0]);
    free(v[0]);
    free(v);

    free(u[0][0]);
    free(u[0]);
    free(u);

    /* check solution for how to count FLOPs!! */
}
