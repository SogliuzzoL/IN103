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
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;

  if ( (left < size) && (tab[left] > tab[largest]) ) {
    largest = left;
  }

  if ( (right < size) && (tab[right] > tab[largest]) ) {
    largest = right;
  }

  if (largest != i) {
    double temp = tab[i];
    tab[i] = tab[largest];
    tab[largest] = temp;
    max_heapify (tab, size, largest);
  }
}

void build_max_heap (double* tab, int size) {
  /* Mieux partir du noeud floor(size / 2), le dernier noeud interne
     avant les feuilles */
  for (int i = size-1; i >= 0; i--) {
    max_heapify (tab, size, i);
  }
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
