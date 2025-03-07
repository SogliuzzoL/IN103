#include <stdlib.h>
#include <stdio.h>
#include "points2d.h"
#include "convex.h"

int main (void) {

  int size = 0;
  fscanf(stdin, "%d", &size);

  point_t** points = malloc (sizeof(point_t*) * size);
  if (points == NULL) {
    return EXIT_FAILURE;
  }

  for (int i = 0; i < size; i++) {
    double x = 0.0;
    double y = 0.0;
    fscanf(stdin, "%lf, %lf", &x, &y);

    points[i] = makePoint (x, y);
  }

  int hull_points = 0;
  point_t** hull = malloc (sizeof(point_t*) * 4);
  if (hull == NULL) {
    return EXIT_FAILURE;
  }

  convex_hull (points, size, &hull, &hull_points);
  for (int i = 0; i < hull_points; i++) {
    printPoint (hull[i]);
    printf ("\n");
  }

  for (int i = 0; i < size; i++) {
    destroyPoint(points[i]);
  }
  free(hull);

  return EXIT_SUCCESS;
}
