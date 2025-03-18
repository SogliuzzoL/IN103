#include <stdlib.h>
#include <stdio.h>

#include "integer_stree.h"

int main (void) {

  int array[] = { 1, 3, 5, 7, 9, 11 };
  int n = sizeof(array) / sizeof(array[0]);

  for (int i = 0; i < n; i++) {
    printf ("array[%d] = %d, ", i, array[i]);
  }
  printf ("\n");

  integer_stree_t stree;
  integer_stree_init (&stree);

  printf ("Build segment tree\n");
  integer_stree_build (&stree, array, n);

  printf ("Taille de l'abre de segments: %d\n", integer_stree_size (&stree));

  for (int i = 0; i < integer_stree_max_size (&stree); i++) {
    printf ("tree[%d] = %d, ", i, stree.tree[i]);
  }
  printf("\n");

  int left = 1;
  int right = 3;
  int result = 0;
  int code = integer_stree_query (&stree, left, right, &result);
  if (code == 0) {
    /* Should print: sum[1, 3] = 15 */
    printf ("sum [%d, %d] = %d\n", left, right, result);
  }
  else {
    printf ("sum [%d, %d] = ERROR\n", left, right);
  }

  printf("Update array[1] = 10\n");
  integer_stree_update (&stree, 1, 10);

  code = integer_stree_query (&stree, left, right, &result);
  if (code == 0) {
    /* Should print: sum[1, 3] = 22 */
    printf ("sum [%d, %d] = %d\n", left, right, result);
  }
  else {
    printf ("sum [%d, %d] = ERROR\n", left, right);
  }

  integer_stree_destroy(&stree);

  return EXIT_SUCCESS;
}
