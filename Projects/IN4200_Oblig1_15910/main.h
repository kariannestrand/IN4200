#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

/* declaration of methods inside read_graph_from_file.c */
void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val);

/* declaration of methods inside PageRank_iterations.c */
void PageRank_iterations(int N, int *row_ptr, int *col_idx, double *val, double d, double epsilon, double *scores);

/* declaration of methods inside top_n_webpages.c */
void top_n_webpages(int N, double *scores, int n);

/* declaration of methods inside method.c */
void swap(int *xp, int *yp);
void sort_relative(int *a, int *b, int n);
void sort_internal(int *arr,  int start, int stop);

#endif
