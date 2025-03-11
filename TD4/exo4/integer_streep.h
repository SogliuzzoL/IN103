#ifndef __INTEGER_STREEP_H__
#define __INTEGER_STREEP_H__

typedef struct integer_streep_t {
  int size; /**< nombre d'éléments dans le tableau initial  */
  int max_size; /**< nombre d'élément dans l'arbre */
  int *tree; /**< tableau représentant l'arbre de segment */
  int (*combine)(int, int);
  int neutral_elemt;
} integer_streep_t;

void integer_streep_init (integer_streep_t* streep, int (*)(int, int), int neutral_elemt);

void integer_streep_destroy (integer_streep_t* streep);

int integer_streep_build (integer_streep_t* streep, int* datas, int n);

int integer_streep_size (integer_streep_t* streep);

int integer_streep_max_size (integer_streep_t* streep);

int integer_streep_query (integer_streep_t* streep, int qs, int qe, int *result);

int integer_streep_update (integer_streep_t* streep, int index, int value);

#endif
