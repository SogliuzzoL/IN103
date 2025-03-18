#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_array_aux (int* array, int size, int start, int end, char* str) {
  if (start < 0 || end > size) {
    return;
  }

  printf ("%s : start = %d and end = %d\n", str, start, end);
  if (start == end) {
    printf ("array[%d] = %d\n", start, array[start]);
    return;
  }

  int mid = (start + end) / 2;
  print_array_aux (array, size, start, mid, "left");
  print_array_aux (array, size, mid + 1, end, "right");
}

void print_array (int* array, int size) {
  print_array_aux (array, size, 0, size-1, "whole");
}

int main (void) {

  int array[] = { 1, 3, 5, 7, 9, 11 };
  int n = sizeof(array) / sizeof(array[0]);

  print_array (array, n);

  return 0;
}
