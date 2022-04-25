#ifndef FUNCTIONS_
#define FUNCTIONS_

/* needed header files .... */
#include <stdio.h>

/*
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <mpi.h>
#include <omp.h>
#include <float.h>
#include <string.h>
*/

#ifdef __MACH__     // indicates if we are on Macintosh operating system or not
#include <stdlib.h>
#else
#include <malloc.h>
#endif

/* data structure to store the m x n pixel values */
typedef struct{
    float** image_data;  /* a 2D array of floats */
    int m;               /* # pixels in vertical-direction */
    int n;               /* # pixels in horizontal-direction */
} image;


/* declarations of functions */
void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);


/* declarations of functions from the JPEG library */
void import_JPEG_file(const char* filename, unsigned char** image_chars,
                      int* image_height, int* image_width,
                      int* num_components);

void export_JPEG_file(const char* filename, const unsigned char* image_chars,
                      int image_height, int image_width,
                      int num_components, int quality);

#endif
