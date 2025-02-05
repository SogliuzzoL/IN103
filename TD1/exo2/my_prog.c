#include <stdlib.h>
#include <stdio.h>

#include "gs.h"
#include "blas.h"

int main(int argc, char *argv[])
{

  int n = 3;
  int size = 3;
  double **vectors;
  vectors = malloc(n * sizeof(double *));
  if (vectors == NULL)
  {
    return EXIT_FAILURE;
  }
  for (int i = 0; i < n; i++)
  {
    vectors[i] = malloc(size * sizeof(double));
    if (vectors[i] == NULL)
    {
      return EXIT_FAILURE;
    }
  }

  vectors[0][0] = 1.0;
  vectors[0][1] = 0.0;
  vectors[0][2] = 1.0;

  vectors[1][0] = 1.0;
  vectors[1][1] = 1.0;
  vectors[1][2] = 1.0;

  vectors[2][0] = -1.0;
  vectors[2][1] = -1.0;
  vectors[2][2] = 0.0;

  printf("Before GS:\n");
  for (int i = 0; i < n; i++)
  {
    printV(size, vectors[i]);
    printf("\n");
  }
  printf("\n");

  gram_schmidt(n, size, vectors);

  printf("After GS:\n");
  for (int i = 0; i < n; i++)
  {
    printV(size, vectors[i]);
    printf("\n");
  }

  return EXIT_SUCCESS;
}
