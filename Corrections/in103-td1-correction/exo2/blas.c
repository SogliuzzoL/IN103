#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "blas.h"

vector_t axby (int size, vector_t x, vector_t y, double alpha, double beta)
{
  int i = 0;
  vector_t result = malloc (size * sizeof(double));
  if (result == NULL) {
    return result;
  }

  for (i = 0; i < size; i++) {
    result[i] = alpha * x[i] + beta * y[i];
  }

  return result;
}

double dot (int size, vector_t x, vector_t y) {
  int i = 0;
  double result = 0.0;
  for (i = 0; i < size; i++) {
    result += x[i] * y[i];
  }

  return result;
}

double norm2 (int size, vector_t x) {
  int i = 0;
  double result = 0.0;

  for (i = 0; i < size; i++) {
    result += x[i] * x[i];
  }

  return sqrt(result);
}

vector_t normalize (int size, vector_t x) {
  return axby (size, x, x, 1.0 / norm2(size, x), 0.0);
}

void printV (int size, vector_t x) {
  int i = 0;
  printf ("(");
  for (i = 0; i < size - 1; i++) {
    printf ("%f, ", x[i]);
  }
  printf ("%f)", x[size-1]);
}
