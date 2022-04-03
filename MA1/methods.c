#include "main.h"

/*
 *  function:  swap
 * --------------------
 *  swaps values such that the value of the first input argument becomes the
 *  value of the other and vice versa
 *
 *  xp: integer that is assigned the value of yp inside the function
 *  yp: integer that is assigned the value of xp inside the function
 */
void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


/*
 *  function:  sort_relative
 * --------------------
 *  sorts 1D array into ascending order and sorts another array into
 *  corresponding indices
 *
 *  a: 1D array being sorted into ascending order
 *  b: 1D array being sorted into the order with corresponding indices
 *  n: size of arrays
 */
void sort_relative(int *a, int *b, int n){
    size_t i, j, min_idx;
    for (i = 0; i < n - 1; i++){
        min_idx = i;
        for (j = i + 1; j < n; j++){
            if (a[j] < a[min_idx]){
                min_idx = j;
            }
        }
        swap(&(a[min_idx]), &(a[i]));
        swap(&(b[min_idx]), &(b[i]));
    }
}


/*
 *  function:  sort_internal
 * --------------------
 *  sorts a 1D array into ascending order from index start to index stop
 *
 *  arr: 1D array of which selections are being sorted into ascending order
 *  start: index at which to start sorting
 *  stop: index at which to stop sorting
 */
void sort_internal(int *arr, int start, int stop){
    if (start < stop - 1){
        int l = start + 1;
        int r = stop;
        while (l < r){
            if (arr[l] <= arr[start]){
                l++;
            }
            else{
                swap(&arr[l], &arr[--r]);
            }
        }
        swap(&arr[--l], &arr[start]);
        sort_internal(arr, start, l);
        sort_internal(arr, r, stop);
    }
}
