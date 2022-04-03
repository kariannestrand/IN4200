# README for IN4200 - Mandatory Assignment 1

## This program uses the C programming language to read a file containing a web graph and store the corresponding hyperlink matrix in CRS format. The scores of each webpage are then calculated using the PageRank algorithm, which is parallelized using OpenMP.

The program is structured into six files:
  - `main.c`
    - Main program that accepts the command line arguments and calls the three functions `read_graph_from_file()`, `PageRank_iterations()` and `top_n_webpages()`.
  - `main.h`
    - Header file containing all file inclusion directives and method declarations.
  - `read_graph_from_file.c`
    - File containing the method `read_graph_from_file()`.
  - `PageRank_iterations.c`
    - File containing the method `PageRank_iterations()`.
  - `top_n_webpages.c`
    - File containing the method `top_n_webpages()`.
  - `methods.c`
    - File containing supplementary methods.
  - `makefile`
    - File to compile and build the program


To compile the code, write the following in the command line:

      make all

To run the code, write:

      ./main.exe filename d epsilon n

where `filename` is the name of the file with the web graph, `d` is the damping
constant, `epsilon` is the convergence threshold value and `n` is the number of
top webpages being printed.
