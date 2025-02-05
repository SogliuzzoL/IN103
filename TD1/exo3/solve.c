#include <math.h>
#include "solve.h"

solution_t solve_2nd_degree(double a, double b, double c)
{

  solution_t roots;
  double discriminant = b * b - 4.0 * a * c;

  if (discriminant > 0)
  {
    /* two real solutions */
    roots.sol1 = makeC((-b + sqrt(discriminant)) / (2.0 * a), 0.0);
    roots.sol2 = makeC((-b - sqrt(discriminant)) / (2.0 * a), 0.0);
  }
  else if (discriminant < 0)
  {
    /* two complex solutions */
    roots.sol1 = makeC(-b / (2.0 * a), sqrt(-discriminant) / (2.0 * a));
    roots.sol2 = makeC(-b / (2.0 * a), -sqrt(-discriminant) / (2.0 * a));
  }
  else
  {
    /* same real solutions */
    roots.sol1 = makeC(-b / (2.0 * a), 0.0);
    roots.sol2 = makeC(-b / (2.0 * a), 0.0);
  }

  return roots;
}
