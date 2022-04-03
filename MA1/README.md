# README for IN4200 - Mandatory Assignment 1

## This program uses the C programming language to read a file containing a web graph and store the corresponding hyperlink matrix in CRS format. The scores of each webpage are then calculated using the PageRank algorithm, which is parallelized using OpenMP.

The program contains six files:
  main.c -


To compile the code, write the following in the command line:

      make all

To run the code, write:

      ./main.exe filename d epsilon n

where 'filename' is the name of the file with the web graph, 'd' is the damping
constant, 'epsilon' is the convergence threshold value and 'n' is the number of
top webpages being printed.
