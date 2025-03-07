#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <integer_list.h>
#include <integer_bitree.h>
#include <integer_bitreealg.h>

void print_integer_list(integer_list_t *list)
{
  integer_list_elmt_t *elmt = integer_list_head(list);
  while (elmt)
  {
    printf("%d ", integer_list_data(elmt));
    elmt = integer_list_next(elmt);
  }
  printf("\n");
}

int main()
{
  integer_bitree_t tree;
  integer_bitree_init(&tree);
  integer_bitree_ins_left(&tree, NULL, 1);

  integer_bitreenode_t *root = integer_bitree_root(&tree);
  integer_bitree_ins_left(&tree, root, 2);
  integer_bitree_ins_right(&tree, root, 3);

  integer_bitreenode_t *left = integer_bitree_left(root);
  integer_bitree_ins_left(&tree, left, 4);
  integer_bitree_ins_right(&tree, left, 5);

  integer_bitreenode_t *right = integer_bitree_right(root);
  integer_bitree_ins_right(&tree, right, 6);

  integer_bitreenode_t *rightright = integer_bitree_right(right);
  integer_bitree_ins_left(&tree, rightright, 7);

  integer_list_t inorder;
  integer_list_init(&inorder);
  integer_inorder(root, &inorder);
  printf("Ordre infixe : ");
  print_integer_list(&inorder);

  integer_list_t preorder;
  integer_list_init(&preorder);
  integer_preorder (root, &preorder);
  printf("Ordre préfixe : ");
  print_integer_list(&preorder);

  integer_list_t postorder;
  integer_list_init(&postorder);
  integer_postorder(root, &postorder);
  printf("Ordre postfixe : ");
  print_integer_list(&postorder);
  
  integer_list_destroy(&inorder);
  integer_list_destroy(&preorder);
  integer_list_destroy(&postorder);

  integer_bitree_destroy(&tree);

  return EXIT_SUCCESS;
}
