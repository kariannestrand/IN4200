
/*
The whole idea here is just to perform the swaps in the perm array rather than in the
unsorted array itself. Beyond that, just make sure that all accesses to arr
is done via perm.

As a followup question, imagine you have the sorted array and the perm array,
and you wish to create an inverse permutation array, such that
sorted[invperm[i]] = arr[i], where arr is the original array. How would you do this?
*/

void swap(int *a, int *b){
    int t = *a; *a = *b; *b = t;
}

void sort_perm(int *arr, int *perm, int beg, int end){
    if (end > beg + 1){
      int piv = arr[perm[beg]], l = beg + 1, r = end;
      while (l < r){
          if (arr[perm[l]] <= piv)
              l++;
          else
              swap(&perm[l], &perm[--r]);
      }
      swap(&perm[--l], &perm[beg]);
      sort_perm(arr, perm, beg, l);
      sort_perm(arr, perm, r, end);
  }
}
