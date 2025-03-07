#include <stdlib.h>
#include <stdio.h>

#include "bistree.h"
#include "bitreealg.h"
#include "stack.h"

int main(int argc, char **arg)
{
  integer_bistree_t tree;
  integer_bistree_init(&tree);

  int x = 0;
  while ((fscanf(stdin, "%d", &x)) != EOF)
  {
    integer_bistree_insert(&tree, x);
  }

  generic_list_t list;
  generic_list_init(&list, NULL, NULL, NULL);
  generic_bitreenode_t *root = generic_bitree_root(&tree);
  generic_inorder(root, &list);
  int listSize = generic_list_size(&list);
  generic_list_elmt_t *elmt = generic_list_head(&list);
  integer_stack_t stack;
  integer_stack_init(&stack);

  for (int i = 0; i < listSize; i++)
  {
    integer_stack_push(&stack, ((integer_avlnode_t *)generic_list_data(elmt))->data);
    elmt = generic_list_next(elmt);
  }

  int data;
  for (int i = 0; i < listSize; i++)
  {
    integer_stack_pop(&stack, &data);
    printf("%d\n", data);
  }

  generic_list_destroy(&list);
  integer_bistree_destroy(&tree);

  return EXIT_SUCCESS;
}
