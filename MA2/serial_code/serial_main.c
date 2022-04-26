#include "functions.h"

int main(int argc, char *argv[]){

    /* declearation of variables */
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;


    /* command line arguments */
    kappa = atof(argv[1]);             // scalar constant
    iters = atoi(argv[2]);             // number of smoothing iterations
    input_jpeg_filename = argv[3];     // filename of the noisy JPG image
    output_jpeg_filename = argv[4];    // filename of the denoised JPG image
    if (argc < 5) {
        printf("Usage: ./prog kappa iters input_jpeg_filename output_jpeg_filename \n");
        return 1;
    }


    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    printf("Succeeded! m: %d, n: %d, c: %d \n", m, n, c);

    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);

    convert_jpeg_to_image(image_chars, &u);
    iso_diffusion_denoising(&u, &u_bar, kappa, iters);

    convert_image_to_jpeg(&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image(&u);
    deallocate_image(&u_bar);


    return 0;
}
