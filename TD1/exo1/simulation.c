#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heun-euler.h"

int main(int argc, char *argv[])
{
  const unsigned int dimension = sinCosDimension();
  double t = 0;
  const double tend = 20.0;
  double h = 0.01;
  const double rtol = 1e-5;
  const double atol = 1e-6;

  int flagRejected = 0;
  double *x1 = NULL;
  double *x0 = sinCosInit();
  double *error = (double *)malloc(sizeof(double) * dimension);

  int nbStep = 0;
  int nbAccepted = 0;
  int nbRejected = 0;

  double estimatedError = 0.0;
  double acceptableError = 0.0;

  if (x0 == NULL)
  {
    perror("x0 allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  if (error == NULL)
  {
    perror("error allocaltion : Empty memory!\n");
    free(x0);
    exit(EXIT_FAILURE);
  }

  /* Initial value for the considered problem: sinCos */
  /* x0[0] = 1.0; */
  /* x0[1] = 0.0; */

  /* Main simulation loop. */
  while (t <= tend)
  {
    x1 = oneStep(sinCos, dimension, t, x0, h, &error);

    /* Integration step-size handler and event detector
     *
     * Compute an estimation of the truncation error and an acceptable
     * error from xi, xi+1, zi+1
     *
     * Increase the integration step size h if estimated error is less
     * than acceptable error except when it follows a rejected step.
     *
     * Decrease the integration step size otherwise.
     */
    estimatedError = norm2(error, dimension);
    acceptableError = atol + rtol * fmax(norm2(x1, dimension), norm2(x0, dimension));
    free(error);
    if (estimatedError < acceptableError)
    {
      /* Accepted integration step */
      printf("%f ", t);
      printVector(x1, dimension);
      free(x0);

      t += h;
      x0 = x1;

      /* ************************************** */

      if (flagRejected == 0)
      {
        /* Increase integration step size because it does not follow a
           rejected step */
        h *= fmin(5, fmax(0.5, 0.9 * pow(1.0 / estimatedError, 1.0 / 2.0)));
      }
      else
      {
        /* Let integration step size unchanged because it follows a
           rejected step */
        flagRejected = 0;
        h *= 1.0;
      }
      nbAccepted++;
    }
    else
    {
      /* Rejected integration step so decrease integration step
   size */
      h *= 0.5;
      flagRejected = 1;
      nbRejected++;
    }
    nbStep++;
  }

  /* For statitics */
  printf("Steps,Rejected,Accepted\n%d,%d,%d\n", nbStep, nbRejected, nbAccepted);

  return EXIT_SUCCESS;
}
