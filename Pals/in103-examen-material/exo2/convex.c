#include <stdlib.h>
#include <stdio.h>
#include "points2d.h"

/* Three points are a counter-clockwise turn if ccw > 0, clockwise if
 * ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
 * gives the signed area of the triangle formed by p1, p2 and p3.
 */
static int orientation(point_t* p1, point_t* p2, point_t* p3)
{
  double value = (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x);
  if ( ((int)value) == 0) {
    return 0;
  }
  return (value > 0.0) ? 1 : 2;
}

/* Returns a list of points on the convex hull in clockwise order.
 */
void convex_hull(point_t** points, int npoints, point_t*** out_hull, int* out_hullsize)
{

  if (npoints < 3) {
    return;
  }

  point_t** hull;

  hull = *out_hull;

  int left = 0;
  for (int i = 0; i < npoints; i++) {
    if (points[i] -> x < points[left] -> x) {
      left = i;
    }
  }

  int p = left;
  int q;
  *out_hullsize = 0;
  do {
    hull[(*out_hullsize)++] = points[p];

    q = (p+1) % npoints;
    for (int i = 0; i < npoints; i++) {
      if (orientation(points[p], points[i], points[q]) == 2) {
	q = i;
      }
    }

    p = q;
  } while (p != left);

  *out_hull = hull;
}
