#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void check_monotony(integer_list_t *list)
{
  bool cst = 1;
  bool incr = 1;
  bool decr = 1;
  bool first = 1;
  bool equality = 0;
  int data;
  int last;

  integer_list_elmt_t *elmt = integer_list_head(list);
  while (elmt != NULL)
  {
    data = integer_list_data(elmt);
    if (first)
    {
      first = 0;
    }
    else if (data == last)
    {
      equality = 1;
    }
    else if (data > last)
    {
      cst = 0;
      decr = 0;
    }
    else if (data < last)
    {
      cst = 0;
      incr = 0;
    }

    if (!(cst + incr + decr))
    {
      break;
    }

    last = data;
    elmt = integer_list_next(elmt);
  }

  if (cst)
  {
    printf("constant\n");
  }
  else if (incr && !equality)
  {
    printf("strictly increasing\n");
  }
  else if (incr)
  {
    printf("increasing\n");
  }
  else if (decr && !equality)
  {
    printf("strictly decreasing\n");
  }
  else if (decr)
  {
    printf("decreasing\n");
  }
  else
    printf("not monotone\n");
}

int main(void)
{
  integer_list_t list;
  integer_list_init(&list);

  int n = 0;

  while (fscanf(stdin, "%d", &n) != EOF)
  {
    integer_list_ins_next(&list, integer_list_tail(&list), n);
  }

  check_monotony(&list);

  integer_list_destroy(&list);

  return 0;
}
