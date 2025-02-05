#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ************************************ */
/* Problem to solve: x' = -y and y' = x */
/* ************************************ */
unsigned int sinCosDimension()
{
  return 2;
}

double *sinCos(double t, double *x)
{
  const unsigned int dimension = sinCosDimension();
  double *res = malloc(sizeof(double) * dimension);
  if (res == NULL)
  {
    perror("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  res[0] = -x[1];
  res[1] = x[0];

  return res;
}

double *sinCosInit()
{
  const unsigned int dimension = sinCosDimension();
  double *res = malloc(sizeof(double) * dimension);
  if (res == NULL)
  {
    perror("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  res[0] = 1.0;
  res[1] = 0.0;

  return res;
}

/* ****************************** */
/* Some linear algebra operations */
/* ****************************** */
double *addVector(double *x, double *y, unsigned int n)
{
  int i = 0;
  double *res = malloc(sizeof(double) * n);
  if (res == NULL)
  {
    perror("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < n; i++)
  {
    res[i] = x[i] + y[i];
  }

  return res;
}

double *gainVector(double a, double *x, unsigned int n)
{
  int i = 0;
  double *res = malloc(sizeof(double) * n);
  if (res == NULL)
  {
    perror("res allocaltion : Empty memory!\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < n; i++)
  {
    res[i] = a * x[i];
  }

  return res;
}

double norm2(double *x, unsigned int n)
{
  int i = 0;
  double res = 0.0;
  for (i = 0; i < n; i++)
  {
    res += x[i] * x[i];
  }

  return sqrt(res);
}

void printVector(double *x, unsigned int n)
{
  int i = 0;
  for (i = 0; i < n - 1; i++)
  {
    printf("%f ", x[i]);
  }
  printf("%f\n", x[i]);
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
double *oneStep(double *(*f)(double, double *), unsigned int n,
                double tInit, double *init, double h, double **error)
{

  double *k1 = NULL;
  double *k2 = NULL;
  double *res1 = NULL;
  double *res2 = NULL;

  k1 = (*f)(tInit, init);
  res1 = addVector(init, gainVector(h, k1, n), n);

  k2 = (*f)(tInit + h, res1);

  res2 = addVector(init, gainVector(h, addVector(gainVector(0.5, k1, n), gainVector(0.5, k2, n), n), n), n);

  *error = addVector(res2, gainVector(-1, res1, n), n);

  return res2;
}