#include <stdlib.h>
#include <stdio.h>

#include "integer_set.h"
#include "list.h"

int main(void)
{
  int size = 0;
  fscanf(stdin, "%d", &size);

  generic_list_t list;
  generic_list_init(&list, NULL, NULL, NULL);
  integer_set_t set;
  generic_list_elmt_t *elmt = NULL;

  for (int i = 0; i < size; i++)
  {

    integer_set_init(&set);
    generic_list_ins_next(&list, elmt, &set);

    if (i == 0)
    {
      elmt = generic_list_head(&list);
    }
    else
      elmt = generic_list_next(elmt);
  }

  int value;
  elmt = generic_list_head(&list);
  integer_set_t *currentSet = elmt->data;
  while ((fscanf(stdin, "%d", &value)) != EOF)
  {
    if (value != 0)
    {
      integer_set_insert(currentSet, value);
    }
    else
    {
      elmt = generic_list_next(elmt);
      currentSet = elmt->data;
    }
  }

  elmt = generic_list_head(&list);
  int listSize = generic_list_size(&list);
  bool overlap = false;

  for (int i = 0; i < listSize - 1; i++)
  {
    generic_list_elmt_t *elmt2 = generic_list_next(elmt);
    for (int j = i + 1; j < listSize; i++)
    {
      integer_set_t interSet;
      integer_set_init(&interSet);

      integer_set_intersection(&interSet, (integer_set_t *)elmt->data, (integer_set_t *)elmt2->data);
      if (!integer_set_size(&interSet))
      {
        overlap = true;
      }

      integer_set_destroy(&set);
      elmt2 = generic_list_next(elmt2);
    }
    elmt = generic_list_next(elmt);
  }

  if (overlap)
  {
    printf("OVERLAP\n");
  }
  else
    printf("DISJOINT\n");

  return 0;
}
