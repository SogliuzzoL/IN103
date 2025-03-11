#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_array_aux (int* array, int size, int start, int end, char* str) {
  /* TODO */
}

void print_array (int* array, int size) {
  /* TODO */
}

int main (void) {

  int array[] = { 1, 3, 5, 7, 9, 11 };
  int n = sizeof(array) / sizeof(array[0]);

  print_array (array, n);

  return 0;
}
