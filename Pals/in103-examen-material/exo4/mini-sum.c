#include <stdlib.h>
#include <stdio.h>
#include "bistree.h"
#include "bitreealg.h"

int main(int argc, char **arg)
{
  int x = 0;
  integer_bistree_t avl;
  integer_bistree_init(&avl);
  while ((fscanf(stdin, "%d", &x)) != EOF)
  {
    integer_bistree_insert(&avl, x);
    if (integer_bistree_size(&avl) < 2)
    {
      printf("-1\n");
    }
    else
    {
      generic_list_t list;
      generic_list_init(&list, NULL, NULL, NULL);
      generic_bitreenode_t *root = generic_bitree_root(&avl);
      generic_inorder(root, &list);
      int listSize = generic_list_size(&list);
      int prod1 = 1;
      int prod2 = 1;
      generic_list_elmt_t *elmt = generic_list_head(&list);
      for (int i = 0; i < listSize; i++)
      {
        if (i == 0 || i == 1)
        {
          prod1 *= ((integer_avlnode_t *)generic_list_data(elmt))->data;
        }

        if (i == listSize - 1 || i == listSize - 2)
        {
          prod2 *= ((integer_avlnode_t *)generic_list_data(elmt))->data;
        }

        elmt = generic_list_next(elmt);
      }

      printf("%d\n", prod1 + prod2);

      generic_list_destroy(&list);
    }
  }

  return EXIT_SUCCESS;
}
