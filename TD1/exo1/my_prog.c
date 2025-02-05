#include <stdlib.h>
#include <stdio.h>
#include "bubble_sort.h"

int main(int argc, char *argv[])
{

  int i;
  int size = 10;
  int array[] = {12, -2, 10, 32, 4, -190, 11, 2, 12, 56};

  printf("Before: ");
  for (i = 0; i < size - 1; i++)
  {
    printf("%d, ", array[i]);
  }
  printf("%d\n", array[size - 1]);

  bubble_sort(array, size);

  printf("After: ");
  for (i = 0; i < size - 1; i++)
  {
    printf("%d, ", array[i]);
  }
  printf("%d\n", array[size - 1]);

  return EXIT_SUCCESS;
}
