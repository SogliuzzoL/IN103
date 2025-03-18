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

int main (){

  int code;
  int size = 7;
  double tab[] = { 0.1, -2.0, 12.3, 3.14159, -1.34, 202.9, -2.67 };
  double* result;
  result = malloc (size * sizeof(double));
  if (result == NULL) {
    return EXIT_FAILURE;
  }

  print_array (tab, size);

  code = heap_sort (tab, size, result);
  if (code == 0) {
    print_array (result, size);
  }

  free(result);
  return EXIT_SUCCESS;
}
