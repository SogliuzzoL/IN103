#ifndef __BLAS_H__
#define __BLAS_H__


#include <stdlib.h>

typedef double* vector_t;

/* Compute alpha * x + beta * y */
/* Assume that x and y have the same size */
vector_t axby (int size, vector_t x, vector_t y, double alpha, double beta);

double dot (int size, vector_t x, vector_t y);

double norm2 (int size, vector_t x);

vector_t normalize (int size, vector_t x);

void printV (int size, vector_t x);

#endif
