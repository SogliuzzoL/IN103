#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "integer_streep.h"

void integer_streep_init (integer_streep_t* streep, int (*combine)(int x, int y), int neutral) {
  /* TODO */
}

void integer_streep_destroy (integer_streep_t* streep) {
  /* TODO */
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
  /* TODO */
  return 0;
}

int integer_streep_build (integer_streep_t* streep, int* datas, int n) {
  /* TODO */
  return 0;
}

static int integer_streep_query_aux (integer_streep_t* streep, int ss, int se, int qs, int qe, int current) {
  /* TODO */
  return 0;
}

int integer_streep_query (integer_streep_t* streep, int qs, int qe, int* result) {
  /* TODO */
  return 0;
}

static void integer_streep_update_aux (integer_streep_t* streep, int ss, int se, int current, int index, int value) {
  /* TODO */
}

int integer_streep_update (integer_streep_t* streep, int index, int value) {
  /* TODO */
  return 0;
}
