#include <stdlib.h>
#include <stdio.h>
#include "set.h"

int main(void)
{
  integer_set_t set;
  integer_set_init(&set);
  int size = 0;
  fscanf(stdin, "%d", &size);

  for (int i = 0; i < size; i++)
  {
    int x;
    fscanf(stdin, "%d", &x);
    integer_set_insert(&set, x);
  }

  int nbRequest = 0;
  fscanf(stdin, "%d", &nbRequest);

  for (int j = 0; j < nbRequest; j++)
  {
    int x = 0;
    fscanf(stdin, "%d", &x);
    if (!integer_set_is_member(&set, x))
    {
      printf("%d\n", x);
    }
  }
  integer_set_destroy(&set);
  return 0;
}
