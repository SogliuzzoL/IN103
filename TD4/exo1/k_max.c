#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void print_array(double *tab, int size)
{
  int i = 0;
  for (i = 0; i < size - 1; i++)
  {
    printf("%f, ", tab[i]);
  }
  printf("%f\n", tab[i]);
}

int k_max(double *tab, int size, double *result, unsigned int k)
{
  real_heap_t heap;
  real_heap_init(&heap, real_MAX_HEAP);
  for (int i = 0; i < size; i++)
  {
    if (real_heap_insert(&heap, tab[i]))
      return -1;
  }

  double data;
  for (int i = 0; i < k; i++)
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
  int k = 4;
  int size = 7;
  double tab[] = {0.1, -2.0, 12.3, 3.14159, -1.34, 202.9, -2.67};
  double *result;
  result = malloc(k * sizeof(double));
  if (result == NULL)
  {
    return EXIT_FAILURE;
  }

  print_array(tab, size);

  code = k_max(tab, size, result, k);

  if (code == 0)
  {
    print_array(result, k > size ? size : k);
  }

  free(result);

  return EXIT_SUCCESS;
}
