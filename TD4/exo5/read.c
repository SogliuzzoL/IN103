#include <stdlib.h>
#include <stdio.h>

int read_int (void) {
  int value;
  fscanf (stdin, "%d", &value);
  return value;
}

int read_array (int* array, int size) {
  int i = 0;
  for (i = 0; i < size; i++) {
    fscanf (stdin, "%d", &array[i]);
  }

  return i;
}
