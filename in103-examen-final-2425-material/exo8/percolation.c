#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int main(void)
{
  int dimension = 0;
  fscanf(stdin, "%d", &dimension);

  integer_list_t list;
  integer_list_init(&list);

  char c = 'a';
  while (fscanf(stdin, "%c", &c) != EOF)
  {
    if (c != '\n')
    {
      integer_list_ins_next(&list, integer_list_tail(&list), c - '0');
    }
  }

  // for (; elmt != NULL; elmt = integer_list_next(elmt))
  // {
  //   printf("%d\n", elmt->data);
  // }

  for (int i = 0; i < dimension; i++)
  {
    integer_list_elmt_t *elmt = integer_list_head(&list);
    for (int j = 0; j < i; j++)
    {
      elmt = integer_list_next(elmt);
    }

    bool isPercolation = true;
    for (int j = 0; j < dimension; j++)
    {
      if (elmt->data == 1)
      {
        isPercolation = false;
        break;
      }
      for (int k = 0; k < dimension; k++)
      {
        if (elmt != NULL)
          elmt = integer_list_next(elmt);
      }
    }
    if (isPercolation)
    {
      printf("PERCOLATION\n");
      return 0;
    }
  }

  printf("PASPERCOLATION\n");
  return 0;
}
