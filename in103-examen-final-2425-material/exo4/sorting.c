#include <stdlib.h>
#include <stdio.h>

#include "bistree.h"
#include "bitreealg.h"

bool check(int i, int p1, int p2, int listSize)
{
  if (i == 0)
    return true;
  int j = 0;
  int n = 0;
  while (j < listSize)
  {
    if (n % 2)
      j += p2;
    else
      j += p1;
    if (i == j)
      return true;
    n++;
  }
  return false;
}

int main(int argc, char **arg)
{

  int p1;
  int p2;
  fscanf(stdin, "%d %d", &p1, &p2);

  integer_bistree_t tree;
  integer_bistree_init(&tree);

  int x = 0;
  while (fscanf(stdin, "%d", &x) != EOF)
  {
    integer_bistree_insert(&tree, x);
  }

  generic_list_t list;
  generic_list_init(&list, NULL, NULL, NULL);
  generic_bitreenode_t *root = generic_bitree_root(&tree);
  generic_inorder(root, &list);
  int listSize = generic_list_size(&list);
  generic_list_elmt_t *elmt = generic_list_head(&list);

  for (int i = 0; i < listSize; i++)
  {
    if (check(i, p1, p2, listSize))
    {
      printf("%d\n", ((integer_avlnode_t *)generic_list_data(elmt))->data);
    }

    elmt = generic_list_next(elmt);
  }

  return EXIT_SUCCESS;
}
