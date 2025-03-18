#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "list.h"

void print_list (integer_list_t *list) {
  integer_list_elmt_t* elt = integer_list_head(list);
  for (; elt != integer_list_tail(list); elt = integer_list_next(elt)) {
    printf ("%d, ", integer_list_data(elt));
  }
  printf ("%d\n", integer_list_data(integer_list_tail(list)));
}

int find_max (integer_list_t *list) {
  int max = INT_MIN;
  integer_list_elmt_t* elt = integer_list_head(list);
  for (; elt != integer_list_tail(list); elt = integer_list_next(elt)) {
    int data = integer_list_data(elt);
    if (data > max) {
      max = data;
    }
  }
  return max;
}

void radix_sort (integer_list_t* initial, integer_list_t* sorted, int max) {
  /* Copy initial into sorted  */
  integer_list_elmt_t* elt = integer_list_head(initial);
  for (; elt != NULL; elt = integer_list_next(elt)) {
    integer_list_ins_next (sorted, integer_list_tail(sorted),
			   integer_list_data(elt));
  }

  for (int exp = 1; exp <= max; exp *= 10) {
    integer_list_t temp;
    integer_list_init (&temp);
    for (int i = 0; i < 10; i++) {
      integer_list_elmt_t* elt = integer_list_head(sorted);
      for (; elt != NULL; elt = integer_list_next(elt)) {
	int data = integer_list_data (elt);
	if ( (data / exp) % 10 == i) {
	  integer_list_ins_next (&temp, integer_list_tail(&temp), data);
	}
      }
    }

    /* Copy temp into sorted after clearing sorted */
    integer_list_destroy(sorted);
    integer_list_init(sorted);

    integer_list_elmt_t* elt = integer_list_head(&temp);
    for (; elt != NULL; elt = integer_list_next(elt)) {
      integer_list_ins_next (sorted, integer_list_tail(sorted),
			     integer_list_data(elt));
    }
    /* A new temp list is created at each iteration */
  }
}

/* Perform radix sort */

int main (){

  int code;
  int i = 0;
  int size = 9;
  int tab[] = {32689, 31320, 22915, 15617, 16203, 4458, 255, 20940, 12335};
  integer_list_t list1;
  integer_list_t list2;

  integer_list_init (&list1);
  integer_list_init (&list2);

  for (i = 0; i < size; i++) {
    code = integer_list_ins_next (&list1, integer_list_tail(&list1), tab[i]);
  }

  print_list (&list1);

  int max = find_max(&list1);
  radix_sort (&list1, &list2, max);

  print_list (&list2);

  return EXIT_SUCCESS;
}
