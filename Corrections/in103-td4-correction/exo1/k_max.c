#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void print_array (double *tab, int size) {
  int i =0;
  for (i =0; i < size - 1; i++) {
    printf ("%f, ", tab[i]);
  }
  printf ("%f\n", tab[i]);
}

int heap_sort (double *tab, int size, double *result) {

  int code;
  int i;
  real_heap_t heap;
  real_heap_init (&heap, real_MIN_HEAP);

  for (i = 0; i < size; i++) {
    code = real_heap_insert (&heap, tab[i]);
    if (code != 0) {
      real_heap_destroy (&heap);
      return EXIT_FAILURE;
    }
  }

  i = 0;
  while (real_heap_size (&heap) > 0) {
    double nb;
    code = real_heap_extract (&heap, &nb);
    if (code != 0) {
      real_heap_destroy (&heap);
      return EXIT_FAILURE;
    }
    result[i] = nb;
    i++;
  }

  real_heap_destroy (&heap);

  return 0;
}

int k_max (double *tab, int size, double *result, unsigned int k) {
  double *sortedTab;
  int code;

  if (k == 0) {
    return 0;
  }
  else if (k > size) {
    k = size;
  }

  sortedTab = malloc (size * sizeof(double));
  if (sortedTab == NULL) {
    return EXIT_FAILURE;
  }

  code = heap_sort (tab, size, sortedTab);
  if (code != 0) {
    return EXIT_FAILURE;
  }


  for (int i = 0; i < k; i++) {
    result[i] = sortedTab[i];
  }

  return 0;
}

/* Find the k greatest value in an array using a max-heap */
int main (){

  int code;
  int k = 4;
  int size = 7;
  double tab[] = { 0.1, -2.0, 12.3, 3.14159, -1.34, 202.9, -2.67 };
  double* result;
  result = malloc (k * sizeof(double));
  if (result == NULL) {
    return EXIT_FAILURE;
  }

  print_array (tab, size);

  code = k_max (tab, size, result, k);

  if (code == 0) {
    print_array (result, k > size ? size : k);
  }

  free(result);

  return EXIT_SUCCESS;
}
