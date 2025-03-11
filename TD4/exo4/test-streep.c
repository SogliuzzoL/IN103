#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "integer_streep.h"

int combine_sum (int x, int y) {
  // neutral_elmt = 0
  return x + y;
}

int combine_prod (int x, int y) {
  // neutral_elmt = 1
  return x * y;
}

int combine_max (int x, int y) {
  // neutral_elmt = INT_MIN
  if (x >= y) {
    return x;
  }
  else {
    return y;
  }
}

int combine_min (int x, int y) {
  // neutral_elmt = INT_MAX
  if (x > y) {
    return y;
  }
  else {
    return x;
  }
}

int main (void) {

  int array[] = { 24, 63, 13, 52, 6, 10, 1 };
  int n = sizeof(array) / sizeof(array[0]);

  for (int i = 0; i < n; i++) {
    printf ("array[%d] = %d, ", i, array[i]);
  }
  printf ("\n");

  integer_streep_t streep;
  integer_streep_init (&streep, combine_sum, 0);

  printf ("Build segment tree\n");
  integer_streep_build (&streep, array, n);

  printf ("Taille de l'abre de segments: %d\n", integer_streep_size (&streep));

  int left = 0;
  int right = 6;
  int result = 0;
  int code = integer_streep_query (&streep, left, right, &result);
  if (code == 0) {
    /* Should print with combine_sum [0, 6] = 169 */
    /* Should print with combine_prod [0, 6] = 61326720 */
    /* Should print with combine_max [0, 6] = 63 */
    /* Should print with combine_min [0, 6] = 1 */
    printf ("[%d, %d] = %d\n", left, right, result);
  }
  else {
    printf ("[%d, %d] = ERROR\n", left, right);
  }

  integer_streep_destroy(&streep);

  return EXIT_SUCCESS;
}
