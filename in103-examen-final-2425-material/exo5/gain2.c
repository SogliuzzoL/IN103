#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int main(void)
{
  integer_list_t list;
  integer_list_init(&list);
  int c = 0;
  while (fscanf(stdin, "%d", &c) != EOF)
  {
    if (c != '\n')
    {
      integer_list_ins_next(&list, integer_list_tail(&list), c);
    }
  }

  integer_list_elmt_t *elmt = integer_list_head(&list);
  for (int i = integer_list_size(&list); i > 0; i--)
  {
    printf("%d\n", elmt->data * i);
    elmt = integer_list_next(elmt);
  }

  return 0;
}
