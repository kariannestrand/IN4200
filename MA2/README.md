# README for IN4200 - Mandatory Assignment 2

### This program uses the C programming language to import a noisy grey-scale image through the external JPEG-library. The image then undergoes simple denoising using the isotropic diffusion algorithm, and a smooth version of the image is exported. The folders `serial_code` and `parallel_code` contains a non-parallelized and MPI parallelized version of this program, respectively. The folder `simple-jpeg` contains the source code of the simple-jpeg external library.

The program in both folders `serial_code` and `parallel_code` is structured into four files:
  - `serial_main.c`/`parallel_main.c`
    - Main program that accepts the command line arguments and calls the necessary functions of the JPEG-library and `functions.c`.
  - `functions.h`
    - Header file containing all file inclusion directives, structures and method declarations.
  - `functions.c`
    - File containing all the methods used in the program.
  - `Makefile`
    - File to compile, build and clean the program.


To compile the code in both folders `serial_code` and `parallel_code`, write the following in the command line:

      make

To run the folder `serial_code`, write:

      ./serial_code kappa iters input_jpeg_filename output_jpeg_filename

where `kappa` is a small scalar constant (such as 0.2 or below).the name of the file with the web graph, `d` is the damping
constant, `epsilon` is the convergence threshold value and `n` is the number of
top webpages being printed.
