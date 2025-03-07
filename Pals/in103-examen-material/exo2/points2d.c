#include <stdlib.h>
#include <stdio.h>
#include "points2d.h"

point_t* makePoint (double x, double y) {
  point_t* p = malloc (sizeof(point_t));
  if (p == NULL) {
    return NULL;
  }

  p->x = x;
  p->y = y;
  return p;
}

void destroyPoint (point_t* p) {
  if (p != NULL) {
    free(p);
  }
}

void printPoint (point_t* p) {
  printf ("(%f, %f)", p->x, p->y);
}
