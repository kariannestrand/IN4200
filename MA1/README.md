# README for IN4200 - Mandatory Assignment 1

## This program uses the C programming language to read a file containing a web graph and store the corresponding hyperlink matrix in CRS format. The scores of each webpage are then calculated using the PageRank algorithm, which is parallelized using OpenMP.

The program is structured into six files:
  - main.c
    - Main program that accepts the command line arguments and calls the three functions `read_graph_from_file`, `PageRank_iterations` and `top_n_webpages`.
  - main.h
    - Header file
  - read_graph_from_file.c
    - Contains a method that reads a file containing a web graph and sort the corresponding hyperlink matrix in CRS format
  - PageRank_iterations.c
    - Contains a method that performs the PageRank algorithm
  - top_n_webpages.c
    - Contains a method that prints out the PageRank scores of the top `n` webpages and their corresponding
  - methods.c
    - Contains supplementary methods


To compile the code, write the following in the command line:

      make all

To run the code, write:

      ./main.exe filename d epsilon n

where `filename` is the name of the file with the web graph, `d` is the damping
constant, `epsilon` is the convergence threshold value and `n` is the number of
top webpages being printed.
