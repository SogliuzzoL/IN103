#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "list.h"

void print_list(integer_list_t *list)
{
  integer_list_elmt_t *elt = integer_list_head(list);
  for (; elt != integer_list_tail(list); elt = integer_list_next(elt))
  {
    printf("%d, ", integer_list_data(elt));
  }
  printf("%d\n", integer_list_data(integer_list_tail(list)));
}

int find_max(integer_list_t *list)
{
  /* TODO */

  return 0;
}

void radix_sort(integer_list_t *initial, integer_list_t *sorted, int max)
{

  /* TODO */
}

int main()
{

  int code;
  int i = 0;
  int size = 9;
  int tab[] = {32689, 31320, 22915, 15617, 16203, 4458, 255, 20940, 12335};
  integer_list_t list1;
  integer_list_t list2;

  integer_list_init(&list1);
  integer_list_init(&list2);

  for (i = 0; i < size; i++)
  {
    code = integer_list_ins_next(&list1, integer_list_tail(&list1), tab[i]);
  }

  print_list(&list1);

  int max = find_max(&list1);
  radix_sort(&list1, &list2, max);

  print_list(&list2);

  return EXIT_SUCCESS;
}
