#include "functions.h"



/*
 *  function:  allocate_image
 * --------------------
 *  allocates the 2D array image_data inside u, when m and n are given as input
 *
 *  u: image structure containing the 2D array image_data
 *  m: the 2D array image_data will be allocated with size (m x n)
 *  n: the 2D array image_data will be allocated with size (m x n)
 */
void allocate_image(image *u, int m, int n){
    int i;
    u->m = m;
    u->n = n;

    // allocating 2D array
    u->image_data = (float **)malloc(m * sizeof(float *));
    u->image_data[0] = (float *)malloc(m * n * sizeof(float));
    for (i = 1; i < m; i++){
        u->image_data[i] = &(u->image_data[0][n * i]);
    }
}



/*
 *  function:  deallocate_image
 * --------------------
 *  frees the storage used by the 2D array image_data inside u
 *
 *  u: image structure containing the 2D array image_data
 */
void deallocate_image(image *u){
    free(u->image_data[0]);
    free(u->image_data);
}



/*
 *  function:  convert_jpeg_to_image
 * --------------------
 *  converts the 1D array image_chars into the image structure u
 *
 *  image_chars: 1D array with unsigned char values
 *  u: image structure
 */
void convert_jpeg_to_image(const unsigned char* image_chars, image *u){
    int i, j;
    int m = u->m;
    int n = u->n;

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            u->image_data[i][j] = image_chars[i * n + j];
        }
    }
}



/*
 *  function:  convert_image_to_jpeg
 * --------------------
 *  converts the 2D array of the image structure into the 1D array image_chars
 *
 *  u: image structure
 *  image_chars: 1D array with unsigned char values
 */
void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    int i, j;
    int m = u->m;
    int n = u->n;

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            image_chars[i * n + j] = u->image_data[i][j];
        }
    }
}



/*
 *  function:  iso_diffusion_denoising
 * --------------------
 *  converts the 2D array of the image structure into the 1D array image_chars
 *
 *  u: image structure
 *  u_bar: image structure
 *  kappa: scalar constant
 *  iters: number of smoothing iterations
 */
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){
    int i, j, k;
    int m = u->m;
    int n = u->n;


    // boundary conditions
    for (i = 0; i < m; i++){
        u_bar->image_data[i][0] = u->image_data[i][0];
        u_bar->image_data[i][n-1] = u->image_data[i][n-1];
    }
    for (j = 0; j < n; j++){
        u_bar->image_data[0][j] = u->image_data[0][j];
        u_bar->image_data[m-1][j] = u->image_data[m-1][j];
    }


    // 2D smoothing function
    for (k = 0; k < iters; k++){
        for (i = 1; i < m-1; i++){
            for (j = 1; j < n-1; j++){
                u_bar->image_data[i][j] = u->image_data[i][j] + kappa
                                          * (u->image_data[i-1][j]
                                          + u->image_data[i][j-1] - 4
                                          * u->image_data[i][j]
                                          + u->image_data[i][j+1]
                                          + u->image_data[i+1][j]);
            }
        }
        swap(u, u_bar);    // after each iteration u and u_bar are swapped
    }
    swap(u_bar, u);        // the last iteration is swapped back
}



/*
 *  function:  swap
 * --------------------
 *  swaps values such that the value of the first input argument becomes the
 *  value of the other and vice versa
 *
 *  u: image structure that is assigned the value of u_bar
 *  u_bar: image structure that is assigned the value of u
 */
void swap(image *u, image *u_bar){
    image temp = *u;
    *u = *u_bar;
    *u_bar = temp;
}
