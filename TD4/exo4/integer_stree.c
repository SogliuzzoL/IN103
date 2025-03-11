#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integer_stree.h"

void integer_stree_init (integer_stree_t* stree) {
  /* TODO */
}

void integer_stree_destroy (integer_stree_t* stree) {
  /* TODO */
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
  /* TODO */
  return 0;
}

int integer_stree_build (integer_stree_t* stree, int* datas, int n) {
  /* TODO */
  return 0;
}

static int integer_stree_query_aux (integer_stree_t* stree, int ss, int se, int qs, int qe, int current) {
  /* TODO */
  return 0;
}

int integer_stree_query (integer_stree_t* stree, int qs, int qe, int* result) {
  /* TODO */
  return 0;
}

static void integer_stree_update_aux (integer_stree_t* stree, int ss, int se, int current, int index, int value) {
  /* TODO */
}

int integer_stree_update (integer_stree_t* stree, int index, int value) {
  /* TODO */
  return 0;
}
