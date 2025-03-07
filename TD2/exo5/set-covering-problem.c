#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "integer_set.h"
#include "integer_list.h"

void print_set(integer_set_t *s)
{
  printf("{ ");
  integer_list_elmt_t *elt = integer_list_head(s);
  for (; elt != integer_list_tail(s) && elt != NULL;
       elt = integer_list_next(elt))
  {
    printf("%d, ", integer_list_data(elt));
  }
  if (integer_list_tail(s) != NULL)
  {
    printf("%d }\n", integer_list_data(integer_list_tail(s)));
  }
}

int indice_min(int *tab, int size)
{
  /* TODO */

  return 0;
}

integer_list_t glouton(integer_set_t *S, int size, integer_set_t *U)
{
  for (int i = 0; i < size; i++)
  {
    integer_set_t *curr = &S[i];
    
  }
  integer_list_t resultat;
  integer_list_init(&resultat);

  return resultat;
}

int main(int argc, char const *argv[])
{
  // Ensemble à couvrir
  integer_set_t U;
  integer_set_init(&U);
  integer_set_insert(&U, 1);
  integer_set_insert(&U, 2);
  integer_set_insert(&U, 4);
  integer_set_insert(&U, 6);
  integer_set_insert(&U, 8);
  integer_set_insert(&U, 9);

  printf("U: ");
  print_set(&U);

  /* Ensembles à utiliser pour couvrir U */
  integer_set_t S0;
  integer_set_t S1;
  integer_set_t S2;
  integer_set_t S3;
  integer_set_t S4;
  integer_set_t S5;
  integer_set_init(&S0);
  integer_set_init(&S1);
  integer_set_init(&S2);
  integer_set_init(&S3);
  integer_set_init(&S4);
  integer_set_init(&S5);

  integer_set_insert(&S0, 1);
  integer_set_insert(&S1, 2);
  integer_set_insert(&S2, 2);
  integer_set_insert(&S2, 4);
  integer_set_insert(&S3, 1);
  integer_set_insert(&S3, 6);
  integer_set_insert(&S3, 8);
  integer_set_insert(&S4, 8);
  integer_set_insert(&S5, 9);

  integer_set_t S[6] = {S0, S1, S2, S3, S4, S5};

  integer_list_t cover = glouton(S, 6, &U);

  printf("U couvert par\n");
  integer_list_elmt_t *elt = integer_list_head(&cover);
  for (; elt != NULL; elt = integer_list_next(elt))
  {
    printf("S%d = ", integer_list_data(elt));
    print_set(&S[integer_list_data(elt)]);
  }

  return 0;
}
