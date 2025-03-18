#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integer_stree.h"

void integer_stree_init (integer_stree_t* stree) {
  stree->size = 0;
  stree->max_size = 0;
  stree->tree = NULL;
}

void integer_stree_destroy (integer_stree_t* stree) {
  stree->size = 0;
  stree->max_size = 0;
  free(stree->tree);
}

int integer_stree_size(integer_stree_t* stree) {
  return stree->size;
}

int integer_stree_max_size(integer_stree_t* stree) {
  return stree->max_size;
}

static inline int get_middle(int left, int right) {
  return (left + right) / 2;
}

static int integer_stree_build_aux (integer_stree_t* stree, int* datas, int ss, int se, int current) {
  if (ss == se) {
    stree->tree[current] = datas[ss];
    return datas[ss];
  }

  int mid = get_middle(ss, se);
  stree->tree[current] =
    integer_stree_build_aux(stree, datas, ss, mid, current * 2 + 1)
    + integer_stree_build_aux(stree, datas, mid + 1, se, current * 2 + 2);
  return stree->tree[current];
}

int integer_stree_build (integer_stree_t* stree, int* datas, int n) {
  int x = (int) (ceil(log2(n))); //Height of segment tree
  int max_size = 2 * (int) pow(2, x) - 1; //Maximum size of segment tree
  stree->tree = malloc (sizeof(int) * max_size);
  if (stree->tree == NULL) {
    return -1;
  }

  integer_stree_build_aux(stree, datas, 0, n - 1, 0);

  stree->size = n;
  stree->max_size = max_size;

  return 0;
}

static int integer_stree_query_aux (integer_stree_t* stree, int ss, int se, int qs, int qe, int current) {
  // If segment of this node is a part of given range, then return the
  // sum of the segment
  if (qs <= ss && qe >= se) {
    return stree->tree[current];
  }

  // If segment of this node is outside the given range
  if (se < qs || ss > qe) {
    return 0;
  }

  // If a part of this segment overlaps with the given range
  int middle = get_middle(ss, se);
  return integer_stree_query_aux (stree, ss, middle, qs, qe, 2 * current + 1) +
    integer_stree_query_aux (stree, middle + 1, se, qs, qe, 2 * current + 2);
}

int integer_stree_query (integer_stree_t* stree, int qs, int qe, int* result) {
  // Check for erroneous input values
  if (qs < 0 || qe > (stree->size - 1) || qs > qe) {
    *result = 0;
    return -1;
  }

  *result = integer_stree_query_aux (stree, 0, integer_stree_size(stree) - 1, qs, qe, 0);
  return 0;
}

static void integer_stree_update_aux (integer_stree_t* stree, int ss, int se, int current, int index, int value) {
  // Base Case: If the input index lies outside the range of this segment
  if (index < ss || index > se) {
    return;
  }

  if (ss == se && ss == index) {
    stree->tree[current] = value;
    return;
  }

  // If the input index is in range of this node, then update the value
  // of the node and its children
  if (se != ss) {
    int middle = get_middle(ss, se);
    integer_stree_update_aux(stree, ss, middle, 2 * current + 1, index, value);
    integer_stree_update_aux(stree, middle + 1, se, 2 * current + 2, index, value);
    stree->tree[current] = stree->tree[current*2+1] + stree->tree[current*2+2];
    return;
  }
}

int integer_stree_update (integer_stree_t* stree, int index, int value) {
  if (index < 0 || index > (integer_stree_size(stree) - 1)) {
    return -1;
  }

  integer_stree_update_aux (stree, 0, integer_stree_size(stree) - 1, 0, index, value);
  return 0;
}
