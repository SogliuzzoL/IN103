#include <stdlib.h>
#include <stdio.h>

#include "complex.h"
#include "solve.h"

int main (int argc, char* argv[]) {

  /* complex_t z1 = makeC (5.0, 2.0); */
  /* complex_t z2 = conjugateC (z1); */

  /* printC (z1); */
  /* printf ("\n"); */
  /* printC (z2); */
  /* printf ("\n"); */
  /* printC (addC(z1,z2)); */
  /* printf ("\n"); */

  /* printf ("%f\n", moduleC(z2)); */
  /* printf ("\n"); */

  /* Complex solutions */
  solution_t rootsC = solve_2nd_degree (3.0, 5.0, 7.0);
  printf ("Solutions of 3x^2 + 5x + 7 are:\n");
  printC (rootsC.sol1);
  printf ("\n");
  printC (rootsC.sol2);
  printf ("\n");
  printf ("\n");

  /* Double real solutions */
  solution_t rootsDR = solve_2nd_degree (4.0, 4.0, 1.0);
  printf ("Solutions of 4x^2 + 4x + 1 are:\n");
  printC (rootsDR.sol1);
  printf ("\n");
  printC (rootsDR.sol2);
  printf ("\n");
  printf ("\n");


  /* Real solutions */
  solution_t rootsR = solve_2nd_degree (2.0, 9.0, -5.0);
  printf ("Solutions of 2x^2 + 9x - 5 are:\n");
  printC (rootsR.sol1);
  printf ("\n");
  printC (rootsR.sol2);
  printf ("\n");
  printf ("\n");


  return EXIT_SUCCESS;
}
