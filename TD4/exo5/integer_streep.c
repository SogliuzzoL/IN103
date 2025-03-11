#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integer_streep.h"

void integer_streep_init (integer_streep_t* streep, int (*combine)(int x, int y), int neutral) {
  streep->size = 0;
  streep->max_size = 0;
  streep->tree = NULL;
  streep->combine = combine;
  streep->neutral_elemt = neutral;
}

void integer_streep_destroy (integer_streep_t* streep) {
  streep->size = 0;
  streep->max_size = 0;
  free(streep->tree);
}

int integer_streep_size(integer_streep_t* streep) {
  return streep->size;
}

int integer_streep_max_size(integer_streep_t* streep) {
  return streep->max_size;
}

static inline int get_middle(int left, int right) {
  return (left + right) / 2;
}

static int integer_streep_build_aux (integer_streep_t* streep, int* datas, int ss, int se, int current) {
  if (ss == se) {
    streep->tree[current] = datas[ss];
    return datas[ss];
  }

  int mid = get_middle(ss, se);
  streep->tree[current] =
    streep->combine (integer_streep_build_aux(streep, datas, ss, mid, current * 2 + 1),
		    integer_streep_build_aux(streep, datas, mid + 1, se, current * 2 + 2));
  return streep->tree[current];
}

int integer_streep_build (integer_streep_t* streep, int* datas, int n) {

  int x = (int) (ceil(log2(n))); //Height of segment tree
  int max_size = 2 * (int) pow(2, x) - 1; //Maximum size of segment tree
  streep->tree = malloc (sizeof(int) * max_size);
  if (streep->tree == NULL) {
    return -1;
  }

  // Fill the allocated memory streep->tree
  integer_streep_build_aux(streep, datas, 0, n - 1, 0);

  streep->size = n;
  streep->max_size = max_size;

  return 0;
}

static int integer_streep_query_aux (integer_streep_t* streep, int ss, int se, int qs, int qe, int current) {
  // If segment of this node is a part of given range, then return the
  // sum of the segment
  if (qs <= ss && qe >= se) {
    return streep->tree[current];
  }

  // If segment of this node is outside the given range
  if (se < qs || ss > qe) {
    return streep->neutral_elemt;
  }

  // If a part of this segment overlaps with the given range
  int middle = get_middle(ss, se);
  return streep->combine (integer_streep_query_aux (streep, ss, middle, qs, qe, 2 * current + 1),
			  integer_streep_query_aux (streep, middle + 1, se, qs, qe, 2 * current + 2));
}

int integer_streep_query (integer_streep_t* streep, int qs, int qe, int* result) {
  // Check for erroneous input values
  if (qs < 0 || qe > (streep->size - 1) || qs > qe) {
    *result = 0;
    return -1;
  }

  *result = integer_streep_query_aux (streep, 0, integer_streep_size(streep) - 1, qs, qe, 0);
  return 0;
}

static void integer_streep_update_aux (integer_streep_t* streep, int ss, int se, int current, int index, int value) {
  // Base Case: If the input index lies outside the range of this segment
  if (index < ss || index > se) {
    return;
  }

  if (ss == se && ss == index) {
    streep->tree[current] = value;
    return;
  }

  // If the input index is in range of this node, then update the value
  // of the node and its children
  if (se != ss) {
    int middle = get_middle(ss, se);
    integer_streep_update_aux(streep, ss, middle, 2 * current + 1, index, value);
    integer_streep_update_aux(streep, middle + 1, se, 2 * current + 2, index, value);
    streep->tree[current] = streep->combine(streep->tree[current*2+1], streep->tree[current*2+2]);
    return;
  }
}

int integer_streep_update (integer_streep_t* streep, int index, int value) {
  if (index < 0 || index > (integer_streep_size(streep) - 1)) {
    return -1;
  }

  integer_streep_update_aux (streep, 0, integer_streep_size(streep) - 1, 0, index, value);
  return 0;
}
