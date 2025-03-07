#include <stdio.h>
#include <stdlib.h>

#include "integer_bistree.h"
#include "bitreealg.h"
#include "integer_list.h"

void print_avlnode_list(generic_list_t *list)
{
  generic_list_elmt_t *elt = generic_list_head(list);
  for (; elt != generic_list_tail(list); elt = generic_list_next(elt))
  {
    printf("%d, ", ((integer_avlnode_t *)generic_list_data(elt))->data);
  }
  printf("%d\n", ((integer_avlnode_t *)generic_list_data(generic_list_tail(list)))->data);
}

int max_height(generic_bitreenode_t *root)
{
  return 0;
}

void add_node(integer_bitree_t *tree, integer_bitreenode_t *current, int elem)
{
  /* A remplir 6 */
}

void print_integer_list(integer_list_t *list)
{
  integer_list_elmt_t *elt = integer_list_head(list);
  for (; elt != integer_list_tail(list); elt = integer_list_next(elt))
  {
    printf("%d, ", integer_list_data(elt));
  }
  printf("%d\n", integer_list_data(integer_list_tail(list)));
}

int main()
{
  int size = 9;
  int tab[] = {32689, 31320, 22915, 15617, 16203, 4458, 255, 20940, 12335}; /* Problem with negative numbers -16203 and below => check rotations! */

  integer_bistree_t tree;
  integer_bistree_init(&tree);

  for (int i = 0; i < size; i++)
  {
    integer_bistree_insert(&tree, tab[i]);
  }

  generic_list_t sorted_avl;
  generic_list_init(&sorted_avl, NULL, NULL, NULL);
  generic_bitreenode_t *root_avl = generic_bitree_root(&tree);
  generic_inorder(root_avl, &sorted_avl);

  print_avlnode_list(&sorted_avl);
  return EXIT_SUCCESS;
}
