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

void max_heapify(double* tab, int size, int i) {
  /* TODO */
}

void build_max_heap (double* tab, int size) {
  /* TODO */
}

int main (){

  int size = 7;
  double tab[] = { 0.1, -2.0, 12.3, 3.14159, -1.34, 202.9, -2.67 };

  printf ("Before: ");
  print_array (tab, size);

  build_max_heap (tab, size);

  printf ("After: ");
  print_array (tab, size);

  return EXIT_SUCCESS;
}
