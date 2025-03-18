#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "integer_set.h"
#include "integer_list.h"
#include "integer_streep.h"
#include "read.h"

/* Solution of exercise : https://codeforces.com/contest/594/problem/D  */

int euclide (int a, int b) { // a > b
  if (b == 0) {
    return a;
  }

  return euclide (b, a % b);
}

void euler_function_1 (int number) {

  int sum = 1;
  for (int i = 2; i < number; i++) {
    if (euclide(number, i) == 1) {
      sum++;
    }
  }
  printf ("%d\n", sum % ((int)(1e9 + 7)));
}


void factorize (int n, integer_set_t* factors) {
  int x = 2;
  while (n > 1) {
    if (n % x == 0) {
      integer_set_insert (factors, x);
      n = n / x;
    }
    else {
      x++;
    }
  }
}

void euler_function_2 (int number) {
  integer_set_t factors;
  integer_set_init (&factors);
  factorize (number, &factors);

  int sum = 1;
  /* Pas necessaire de tester 1 et n car ils sont diviseurs */
  for (int i = 2; i < number; i++) {
    integer_list_elmt_t* elem = integer_list_head (&factors);
    bool flag = false;
    for (; elem != NULL; elem = integer_list_next (elem)) {
      int n = integer_list_data (elem);

      if (i % n == 0) {
	flag = true;
	break;
      }
    }

    if (flag == false) {
      sum++;
    }
  }
  integer_set_destroy (&factors);
  printf ("%d\n", sum % ((int)(1e9 + 7)));
}

int combine_prod (int x, int y) {
  // neutral_elmt = 1
  return x * y;
}

int main (void) {
  int size = read_int ();
  //printf ("%d %d\n", size, INT_MAX);
  int* array = malloc (size * sizeof(int));
  if (array == NULL) {
    return EXIT_FAILURE;
  }
  read_array (array, size);

  integer_streep_t streep;
  integer_streep_init (&streep, combine_prod, 1);

  integer_streep_build (&streep, array, size);

  int nb_req = read_int ();

  while (nb_req-- > 0) {
    int left = 0;
    int right = 0;
    fscanf (stdin, "%d %d", &left, &right);

    int result = 0;
    int code = integer_streep_query (&streep, left-1, right-1, &result);
    if (code == 0) {
      euler_function_2 (result);
    }
  }

  integer_streep_destroy (&streep);
  free (array);
  return EXIT_SUCCESS;
}
