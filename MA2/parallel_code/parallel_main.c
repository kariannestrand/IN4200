#include "functions.h"

int main(int argc, char *argv[]){
    /* declaration of variables */
    int m, n, c, iters;
    int my_m, my_n, my_rank, num_procs;
    float kappa;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;


    /* beginning MPI parallelization */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


    /* command line arguments */
    kappa = atof(argv[1]);             // scalar constant
    iters = atoi(argv[2]);             // number of smoothing iterations
    input_jpeg_filename = argv[3];     // filename of the noisy JPG image
    output_jpeg_filename = argv[4];    // filename of the denoised JPG image
    if (argc < 5) {
        printf("Usage: ./prog kappa iters input_jpeg_filename output_jpeg_filename \n");
        return 1;
    }


    if (my_rank == 0){
       import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
       allocate_image(&whole_image, m, n);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);


    /* 2D decomposition of the m x n pixels evenly among the MPI processes */
    int my_start = (my_rank * m)/num_procs + 1;
    int my_stop = ((my_rank + 1) * m)/num_procs;
    my_m = my_stop - my_start + 1;  // number of vertical pixels per process
    my_n = n;                       // number of horizontal pixels per process

    allocate_image(&u, my_m, my_n);
    allocate_image(&u_bar, my_m, my_n);


    /* creating partitioned region of image_chars for each process */
    int region_size = my_m * my_n;
    my_image_chars = malloc(region_size * sizeof *my_image_chars);
    convert_jpeg_to_image(my_image_chars, &u);
    iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters);


    /* array containing indices at which new regions start */
    int *displs = malloc(num_procs * sizeof *displs);
    for (int i = 0; i < num_procs; i++){
        displs[i] = i * region_size;
    }


    /* array containing the region size of each process */
    int *sendcounts = malloc(num_procs * sizeof *sendcounts);
    MPI_Gather(&region_size, 1, MPI_INT, sendcounts, 1, MPI_INT,
               0, MPI_COMM_WORLD);


    /* filling array my_image_chars with respective image_chars values for
       each process */
    MPI_Scatterv(image_chars, sendcounts, displs, MPI_UNSIGNED_CHAR,
                 my_image_chars, region_size, MPI_UNSIGNED_CHAR, 0,
                 MPI_COMM_WORLD);


    /* sending resulting content of my_image_chars of each process to
       process 0, into the struct whole_image */
    MPI_Gatherv(my_image_chars, region_size, MPI_UNSIGNED_CHAR, image_chars,
                sendcounts, displs, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);


    if (my_rank == 0){
       convert_image_to_jpeg(&whole_image, image_chars);
       export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
       deallocate_image(&whole_image);
    }

    deallocate_image(&u);
    deallocate_image(&u_bar);

    MPI_Finalize();

    return 0;
}
