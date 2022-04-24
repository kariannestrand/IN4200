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
    iters = atoi(argv[2]);             // number of iterations?
    input_jpeg_filename = argv[3];     // filename of the noisy JPG image
    output_jpeg_filename = argv[4];    // filename of the denoised JPG image
    if (argc < 5) {
        printf("Usage: ./prog kappa iters input_jpeg_filename output_jpeg_filename \n");
        return 1;
    }


    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    printf("Succeeded! vertical pixels: %d, horizontal pixels: %d, num components: %d \n",
           m, n, c);


    allocate_image(&u, m, n);
    //allocate_image(&u_bar, m, n);


    /*
    convert_jpeg_to_image(image_chars, &u);

    iso_diffusion_denoising(&u, &u_bar, kappa, iters);

    convert_image_to_jpeg(&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image(&u);
    deallocate_image(&u_bar);
    */



    // example code
    /*
    import_JPEG_file("toys.jpg", &image_chars, &height, &width, &comp);
    printf("Succeeded! vertical pixels: %d, horizontal pixels: %d, num components: %d\n",
       height, width, comp);

    // creating a horizontally flipped image
    new_chars = (unsigned char*)malloc(height*width*comp*sizeof(unsigned char));
    for (i=0; i<height; i++)
      for (j=0; j<width; j++)
        for (k=0; k<comp; k++)
      new_chars[i*(width*comp)+j*comp+k]=image_chars[i*(width*comp)+(width-j-1)*comp+k];

    export_JPEG_file ("flipped_image.jpg", new_chars, height, width, comp, 75);
    */

    return 0;
}
