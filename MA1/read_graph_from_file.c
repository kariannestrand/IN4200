#include "main.h"


/*
 *  function:  read_graph_from_file
 * --------------------
 *  reads a file that contains a web graph and sorts the corresponding
 *  hyperlink matrix into CRS format
 *
 *  filename: name of the file
 *  N: pre-decleared integer assigned as total number of webpages inside the
 *     function
 *  row_ptr: pre-decleared double allocated as a 1D array inside the function,
 *           which stores the indices at which new rows start in val
 *  col_idx: pre-decleared double allocated as a 1D array inside the function,
 *           which stores the column index of each non-zero in val
 *  val: pre-decleared double allocated as a 1D array inside the function,
 *       which stores all non-zeros of the hyperlink matrix
 */
void read_graph_from_file(char *filename, int *N, int **row_ptr, int **col_idx, double **val){
    /* declearation of variables */
    FILE *datafile;
    int edges, *FromNodeId, *ToNodeId;



    /* read from text file */
    datafile = fopen(filename, "r");
    if (datafile == NULL){
        printf("Failed to open file %s \n", filename);
        exit(0);
    }
    fscanf(datafile, "# %*[^#]");                            // reads first line (scans everything from # until next #)
    fscanf(datafile, "# %*[^#]");                            // reads second line (scans everything from # until next #)
    fscanf(datafile, "# Nodes: %d   Edges: %d ", N, &edges); // reads and appoints number of nodes and edges
    fscanf(datafile, "# FromNodeId ToNodeId");               // reads third line

    FromNodeId = malloc(edges * sizeof FromNodeId); // index of the outbound webpage
    ToNodeId = malloc(edges * sizeof ToNodeId);     // index of the inbound webpage
    for (int i = 0; i < edges; i++){
        fscanf(datafile, "%d %d", &FromNodeId[i], &ToNodeId[i]);
    }
    fclose(datafile);



    /* allocating arrays needed to create matrix built in CRS format */
    *row_ptr = malloc((*N + 1) * sizeof *row_ptr);    // stores the indices at which new rows start in val
    *col_idx = malloc(edges * sizeof *col_idx);       // stores the column index of each non-zero in val
    *val = malloc(edges * sizeof *val);               // stores all non-zeros of the hyperlink matrix


    /* creating row_ptr */
    int count = 0;                        // initialize counter
    for (int i = 0; i < (*N + 1); i++){   // goes through all of row_ptr
        for (int j = 0; j < edges; j++){  // goes through all of ToNodeId
            if (ToNodeId[j] == i && ToNodeId[j] != FromNodeId[j]){
                count++;  // counts the frequency of each value when discarding self-linkage
            }
        }
        (*row_ptr)[i+1] = count;  // updates row_ptr
    }


    /* creating col_idx */
    sort_relative(ToNodeId, FromNodeId, edges);
    for (int i = 0; i < *N; i++){
        int start = (*row_ptr)[i];
        int stop = (*row_ptr)[i+1];
        sort_internal(FromNodeId, start, stop);
    }
    *col_idx = FromNodeId;  // updates col_idx


    /* creating val */
    int *temp = malloc(edges * sizeof *temp);  // declearing temporary array
    for (int i = 0; i < edges; i++){
        if (ToNodeId[i] != FromNodeId[i]){     // discarding self-linkage
            temp[(*col_idx)[i]]++;             // counts number of non-zeros in each column
        }
    }
    printf("val: \n");
    for (int i = 0; i < edges; i++){
        (*val)[i] = 1. / temp[(*col_idx)[i]];  // updates val
        printf("%f \n", (*val)[i]);            // prints val
    }



    /* freeing memory of allocated arrays */
    free(ToNodeId);
    free(temp);
}
