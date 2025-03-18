#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <stdlib.h>

typedef struct cpx_ {
  double a;
  double b;
} complex_t;


complex_t makeC (double a, double b);

complex_t addC (complex_t z1, complex_t z2);

complex_t mulC (complex_t z1, complex_t z2);

complex_t conjugateC (complex_t z1);

double moduleC (complex_t z1);

double realPart (complex_t z1);

double complexPart (complex_t z1);

void printC (complex_t z1);

#endif
