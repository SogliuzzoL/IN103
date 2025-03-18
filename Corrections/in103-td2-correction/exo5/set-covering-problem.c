#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "integer_set.h"
#include "integer_list.h"

void print_set(integer_set_t* s) {
  printf ("{ ");
  integer_list_elmt_t* elt = integer_list_head(s);
  for (; elt != integer_list_tail(s) && elt != NULL;
       elt = integer_list_next(elt))
    {
      printf ("%d, ", integer_list_data(elt));
    }
  if (integer_list_tail(s) != NULL) {
    printf ("%d }\n", integer_list_data(integer_list_tail(s)));
  }
}

int indice_min (int* tab, int size) {
  int pos = 0;
  int min = tab[0];
  for (int i = 1; i < size; i++) {
    if (tab[i] < min){
      pos = i;
      min = tab[i];
    }
  }
  return pos;
}

integer_list_t glouton(integer_set_t* S, int size, integer_set_t* U) {
  int all_size[size];

  integer_list_t resultat;
  integer_list_init(&resultat);

  integer_set_t trouve;
  integer_set_t temp;
  integer_set_t reste;
  integer_set_init(&trouve);
  integer_set_init(&temp);
  integer_set_init(&reste);

  while (integer_set_size(&trouve) < integer_set_size(U)) {
    /* On ne garde que les elements de U qui ne sont pas couverts */
    integer_set_difference(&reste, U, &trouve);
    /* On calcule pour chaque S[i] les elements de U encore \`a couvrir
       qui ne sont pas couverts par S[i] */
    for (int i = 0; i < size; i++) {
      integer_set_difference(&temp, &reste, &S[i]);
      all_size[i] = integer_set_size(&temp);
    }

    /* Le plus petit elements de all_size indique l'element S[i] qui
       couvre le plus les elements de U encore \`a couvrir */
    int pos = indice_min (all_size, size);
    integer_set_union(&temp, &S[pos], &trouve);

    /* Astuce pour copier un ensemble dans un autre */
    integer_set_union(&trouve, &temp, &temp);

    /* On garde l'indice i du tableau S qui correspond localement \`a
       S[i] qui couvre le plus U */
    integer_list_ins_next(&resultat, NULL, pos);
  }
  return resultat;
}

int indice_max (int* tab, int size) {
  int pos = 0;
  int max = tab[0];
  for (int i = 1; i < size; i++) {
    if (tab[i] > max){
      pos = i;
      max = tab[i];
    }
  }
  return pos;
}


integer_list_t glouton_v2(integer_set_t* S, int size, integer_set_t* U) {
  int all_size[size];

  integer_list_t resultat;
  integer_list_init(&resultat);

  integer_set_t temp;
  integer_set_t reste;
  integer_set_init(&temp);
  integer_set_init(&reste);

  /* au debut il nous reste tout U \`a trouver */
  integer_set_union(&reste, U, U);

  while (integer_set_size(&reste) > 0) {
    /* On calcule pour chaque S[i] le nombre de nouveaux elements
       qu'il permet de decouvrir */
    for (int i = 0; i < size; i++) {
      integer_set_intersection(&temp, &reste, &S[i]);
      all_size[i] = integer_set_size(&temp);
    }

    /* Le plus grand elements de all_size indique l'element S[i] qui
       couvre le plus les elements de U encore \`a couvrir */
    int pos = indice_max (all_size, size);

    /* on met \`a jour l'ensemble reste */
    integer_set_difference(&temp, &reste, &S[pos]);

    // astuce pour copier une liste dans une autre
    integer_set_union(&reste, &temp, &temp);

    /* On garde l'indice i du tableau S qui correspond localement \`a
       S[i] qui couvre le plus U */
    integer_list_ins_next(&resultat, NULL, pos);
  }
  return resultat;
}

void array_to_set(integer_set_t* set, int* array, int size) {
  integer_set_init(set);
  for (int i = 0; i < size; i++) {
    integer_set_insert(set, array[i]);
  }
}

int application() {
  /* Modelisation du probleme: 13 cameras */
  /* Voir la carte avec la numerotation des cameras et couloirs */
  integer_set_t S[13];
  int data[13][4] = {
    {0, 3, 4, 6},
    {0, 1, 2},
    {1},
    {2},
    {3},
    {4, 8, 5},
    {5, 7, 9},
    {7, 10},
    {8},
    {9},
    {11},
    {12},
    {10, 11, 12}
  };
  /* Tailles des sous ensembles de S */
  int size[13] = {4, 3, 1, 1, 1, 3, 3 ,2, 1, 1, 1, 1, 3};

  for (int i = 0; i < 13; i++) {
    array_to_set(&S[i], data[i], size[i]);
  }

  /* Ensemble \`a couvrir les 13 couloirs de station de metro */
  integer_set_t U;
  integer_set_init(&U);
  for (int i = 0; i < 13; i++) {
    integer_set_insert(&U, i);
  }
  integer_set_t res = glouton(S, 13, &U);
  print_set(&res);

  return 0;
}

int main(int argc, char const *argv[]) {
    // Ensemble \`a couvrir
    integer_set_t U;
    integer_set_init(&U);
    integer_set_insert(&U,1);
    integer_set_insert(&U,2);
    integer_set_insert(&U,4);
    integer_set_insert(&U,6);
    integer_set_insert(&U,8);
    integer_set_insert(&U,9);

    printf("U: ");
    print_set(&U);

    /* Ensembles \`a utiliser pour couvrir U */
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

    integer_set_insert(&S0,1);
    integer_set_insert(&S1,2);
    integer_set_insert(&S2,2);
    integer_set_insert(&S2,4);
    integer_set_insert(&S3,1);
    integer_set_insert(&S3,6);
    integer_set_insert(&S3,8);
    integer_set_insert(&S4,8);
    integer_set_insert(&S5,9);

    integer_set_t S[6]= {S0, S1, S2, S3, S4, S5};

    integer_list_t cover = glouton(S, 6, &U);

    printf("U couvert par\n");
    integer_list_elmt_t* elt = integer_list_head(&cover);
    for (; elt != NULL; elt = integer_list_next(elt)) {
      printf ("S%d = ", integer_list_data(elt) );
      print_set(&S[integer_list_data(elt)]);
    }

    printf("Application: \n");
    application();

    return 0;
}
