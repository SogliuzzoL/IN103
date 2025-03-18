#ifndef __SOLVE_H__
#define __SOLVE_H__


#include "complex.h"

typedef struct solution_ {
  complex_t sol1;
  complex_t sol2;
} solution_t;


solution_t solve_2nd_degree (double a, double b, double c);

#endif
