#include <stdlib.h>
#include <stdio.h>


int bubble_sort (int* array, unsigned int size) {

  int i;
  int j;

  if (array == NULL) {
    return -1;
  }

  for (i = 0; i < size; i++) {
    for (j = i + 1; j < size; j++) {
      if (array[i] > array[j]) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
      }
    }
  }

  return 0;
}


int main (int argc, char* argv[]) {

  int i;
  int size = 5;
  int array[] = {-2, 23, -19, 4, 65};

  printf ("Before: ");
  for (i = 0; i < size - 1; i++) {
      printf ("%d, ", array[i]);
  }
  printf ("%d\n", array[size-1]);

  bubble_sort (array, size);

  printf ("After: ");
  for (i = 0; i < size - 1; i++) {
      printf ("%d, ", array[i]);
  }
  printf ("%d\n", array[size-1]);


  return EXIT_SUCCESS;
}
