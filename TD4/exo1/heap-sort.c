#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void print_array(double *tab, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (i < size - 1)
      printf("%f, ", tab[i]);
    else printf("%f\n", tab[i]);
  }
  
}

int heap_sort(double *tab, int size, double *result, enum real_heap_type_ type)
{
  real_heap_t heap;
  real_heap_init(&heap, type);
  for (int i = 0; i < size; i++)
  {
    if (real_heap_insert(&heap, tab[i]))
      return -1;
  }

  double data;
  for (int i = 0; i < size; i++)
  {
    if (real_heap_extract(&heap, &data))
      return -1;
    result[i] = data;
  }
  real_heap_destroy(&heap);
  return 0;
}

int main()
{

  int code;
  int size = 7;
  double tab[] = {0.1, -2.0, 12.3, 3.14159, -1.34, 202.9, -2.67};
  double *result;
  result = malloc(size * sizeof(double));
  if (result == NULL)
  {
    return EXIT_FAILURE;
  }

  print_array(tab, size);

  code = heap_sort(tab, size, result, real_MIN_HEAP);
  if (code == 0)
  {
    print_array(result, size);
  }

  free(result);

  return EXIT_SUCCESS;
}
