#include <stdlib.h>
#include <stdio.h>

int bubble_sort(int *array, unsigned int size)
{

  int i;
  int j;

  if (array == NULL)
  {
    return -1;
  }

  for (i = 0; i < size; i++)
  {
    for (j = i + 1; j < size; j++)
    {
      if (array[i] > array[j])
      {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }

  return 0;
}
