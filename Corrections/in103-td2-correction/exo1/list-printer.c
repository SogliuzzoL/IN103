#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void print_list (integer_list_t *list) {
  integer_list_elmt_t* elt = integer_list_head(list);
  for (; elt != integer_list_tail(list); elt = integer_list_next(elt)) {
    printf ("%d, ", integer_list_data(elt));
  }
  printf ("%d\n", integer_list_data(integer_list_tail(list)));
}

int main (){

  int code;

  integer_list_t list;
  integer_list_init (&list);

  for (int i = 0; i < 12; i++) {
    code = integer_list_ins_next (&list, integer_list_tail(&list), i);
    if (code != 0) {
      integer_list_destroy (&list);
      return EXIT_FAILURE;
    }
  }

  print_list (&list);

  integer_list_destroy (&list);


  return EXIT_SUCCESS;
}
