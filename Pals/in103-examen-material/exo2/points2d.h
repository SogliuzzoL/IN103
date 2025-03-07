#ifndef __POINT_H__
#define __POINT_H__

typedef struct {
  double x;
  double y;
} point_t;

point_t* makePoint (double x, double y);

void destroyPoint (point_t* p);

void printPoint (point_t* p);
#endif
