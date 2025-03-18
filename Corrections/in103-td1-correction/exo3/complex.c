#include <stdio.h>
#include <math.h>


#include "complex.h"

complex_t makeC (double a, double b) {
  complex_t z;
  z.a = a;
  z.b = b;
  return z;
}

complex_t addC (complex_t z1, complex_t z2) {
  complex_t z;

  z.a = z1.a + z2.a;
  z.b = z1.b + z2.b;

  return z;
}

complex_t mulC (complex_t z1, complex_t z2) {
  complex_t z;
  z.a = z1.a * z2.a - z1.b * z2.b;
  z.b = z1.a * z2.b + z1.b * z2.a;

  return z;
}

complex_t conjugateC (complex_t z1) {
  complex_t z;
  z.a = z1.a;
  z.b = -z1.b;

  return z;
}

double moduleC (complex_t z1) {
  return sqrt(z1.a * z1.a + z1.b * z1.b);
}

double realPart (complex_t z1) {
  return z1.a;
}

double complexPart (complex_t z1) {
  return z1.b;
}

void printC (complex_t z1) {
  //  printf ("%f + i %f", z1.a, z1.b);
  if (z1.b == 0) {
    printf ("%f", z1.a);
  }
  else if (z1.b > 0) {
    printf ("%f + i x %f", z1.a, z1.b);
  }
  else {
    printf ("%f - i x %f", z1.a, fabs(z1.b));
  }
}
