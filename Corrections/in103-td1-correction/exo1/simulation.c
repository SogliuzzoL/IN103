#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* ************************************ */
/* Problem to solve: x' = -y and y' = x */
/* ************************************ */
unsigned int sinCosDimension () {
  return 2;
}

double* sinCos (double t, double* x) {
  const unsigned int dimension = sinCosDimension();
  double* res = malloc (sizeof(double) * dimension);
  if (res == NULL) {
    perror ("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  res[0] = -x[1];
  res[1] = x[0];

  return res;
}

double* sinCosInit() {
  const unsigned int dimension = sinCosDimension();
  double* res = malloc (sizeof(double) * dimension);
  if (res == NULL) {
    perror ("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  res[0] = 1.0;
  res[1] = 0.0;

  return res;
}

/* ****************************** */
/* Some linear algebra operations */
/* ****************************** */
double* addVector (double* x, double* y, unsigned int n) {
  int i = 0;
  double* res = malloc (sizeof(double) * n);
  if (res == NULL) {
    perror ("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < n; i++) {
    res[i] = x[i] + y[i];
  }

  return res;
}

double* gainVector (double a, double* x, unsigned int n) {
  int i = 0;
  double* res = malloc (sizeof(double) * n);
  if (res == NULL) {
    perror ("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < n; i++) {
    res[i] = a * x[i];
  }

  return res;
}

double norm2 (double* x, unsigned int n) {
  int i = 0;
  double res = 0.0;
  for (i = 0; i < n; i++) {
    res += x[i] * x[i];
  }

  return sqrt(res);
}


void printVector (double* x, unsigned int n) {
  int i = 0;
  for (i = 0; i < n-1; i++) {
    printf ("%f ", x[i]);
  }
  printf ("%f\n", x[i]);
}


/* ********************************************************************
 * This function performs one integration step. It should be used into
 * a simulation loop to reach a specific time.
 *
 * \brief Implementation of Heun-Euler Method which is the most simple
 * adaptive Runge-Kutta methods, cf
 * https://en.wikipedia.org/wiki/List_of_Runge-Kutta_methods
 *
 * \param f: the dynamical system to simulate
 *
 * \param n: the dimension of the dynamical system
 *
 * \param tInit: the initial time
 *
 * \param init: the initial condition
 *
 * \param h: the finite horizon for the simulation or the integration
 * step-size
 *
 * \param error: an estimation of the truncation error
 *
 * \return the value of the solution of the dynamical system at time
 * tInit+h */
double* oneStep (double* (*f) (double, double*), unsigned int n,
		 double tInit, double* init, double h, double** error)
{

  double* k1 = NULL;
  double* k2 = NULL;
  double* res1 = NULL;
  double* res2 = NULL;


  k1 = (*f)(tInit, init);
  res1 = addVector (init, gainVector(h, k1, n), n);

  k2 = (*f)(tInit+h, res1);

  res2 = addVector(init, gainVector(h, addVector(gainVector (0.5, k1, n), gainVector(0.5, k2, n), n), n), n);

  *error = addVector(res2, gainVector (-1, res1, n), n);

  return res2;
}

int main (int argc, char* argv[]) {
  const unsigned int dimension = sinCosDimension ();
  double t = 0;
  const double tend = 20.0;
  double h = 0.01;
  const double rtol = 1e-5;
  const double atol = 1e-6;

  int flagRejected = 0;
  double* x1 = NULL;
  double* x0 = sinCosInit();
  double* error = (double*) malloc (sizeof(double) * dimension);

  int nbStep = 0;
  int nbAccepted = 0;
  int nbRejected = 0;

  double estimatedError = 0.0;
  double acceptableError = 0.0;

  if (x0 == NULL) {
    perror ("x0 allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  if (error == NULL) {
    perror ("error allocaltion : Empty memory!\n");
    free(x0);
    exit(EXIT_FAILURE);
  }

  /* Initial value for the considered problem: sinCos */
  /* x0[0] = 1.0; */
  /* x0[1] = 0.0; */

  /* Main simulation loop. */
  while (t <= tend) {
    x1 = oneStep (sinCos, dimension, t, x0, h, &error);

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
    estimatedError = norm2 (error, dimension);
    acceptableError = atol +  rtol * fmax(norm2(x1, dimension), norm2(x0,dimension));
    free(error);
    if (estimatedError < acceptableError) {
      /* Accepted integration step */
      printf ("%f ", t);
      printVector (x1, dimension);
      free(x0);


      t += h;
      x0 = x1;

      /* ************************************** */


      if (flagRejected == 0) {
	/* Increase integration step size because it does not follow a
	   rejected step */
    	h *= fmin(5, fmax(0.5, 0.9 * pow(1.0 / estimatedError, 1.0/2.0)));
      }
      else {
	/* Let integration step size unchanged because it follows a
	   rejected step */
    	flagRejected = 0;
    	h *= 1.0;
      }
      nbAccepted++;
    }
    else {
      /* Rejected integration step so decrease integration step
	 size */
      h *= 0.5;
      flagRejected = 1;
      nbRejected++;
    }
    nbStep++;
  }

  /* For statitics */
  printf ("Steps,Rejected,Accepted\n%d,%d,%d\n", nbStep, nbRejected, nbAccepted);

  return EXIT_SUCCESS;
}
