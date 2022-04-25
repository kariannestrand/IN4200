#include "functions.h"

void allocate_image(image *u, int m, int n){
    //int i, j;

    /*
    Function allocate image is supposed to allocate the 2D array image data
    inside u, when m and n are given as input.
    */

    // allocating array image_data


    /*
    u->image_data = (float **)malloc(u->m * sizeof(float *));
    u->image_data[0] = (float *)malloc(u->m * u->n * sizeof(float));
    for (i = 1; i < u->m; i++){
        u->image_data[i] = &(u->image_data[0][u->n * i]);
    }
    */

    // filling image_data with image data
    /*
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            image_data[i][j] = = u;
        }
    }
    */
}

void deallocate_image(image *u){
    /*
    The purpose of function deallocate image is to free the storage used by
    the 2D array image data inside u.
    */

}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u){

}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){

}

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){

}
