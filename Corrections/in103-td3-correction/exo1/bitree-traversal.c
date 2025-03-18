#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bitree.h"
#include "bitreealg.h"

void print_integer_list (integer_list_t* list) {
  integer_list_elmt_t *elt;
  for (elt = integer_list_head(list);
       elt != integer_list_tail(list);
       elt = integer_list_next (elt)) {
    printf ("%d, ", integer_list_data(elt));
  }
  printf ("%d\n", integer_list_data(integer_list_tail(list)));
}

int main () {
  integer_bitree_t tree;
  integer_bitree_init (&tree);

  /* Particularite de la bibliotheque pour l'insertion dans la racine */
  integer_bitree_ins_left (&tree, NULL, 1);
  printf ("Root takes value 1\n");

  integer_bitreenode_t* root = integer_bitree_root (&tree);
  integer_bitree_ins_left (&tree, root, 2);
  printf ("Root->left takes value 2\n");
  integer_bitree_ins_right (&tree, root, 3);
  printf ("Root->right takes value 3\n");

  integer_bitreenode_t* left = integer_bitree_left(root);
  integer_bitree_ins_left (&tree, left, 4);
  printf ("Root->left->left takes value 4\n");
  integer_bitree_ins_right (&tree, left, 5);
  printf ("Root->left->right takes value 5\n");

  integer_bitreenode_t* right = integer_bitree_right(root);
  integer_bitree_ins_right (&tree, right, 6);
  printf ("Root->right->right takes value 6\n");

  integer_bitreenode_t* rightright = integer_bitree_right(right);
  integer_bitree_ins_left (&tree, rightright, 7);
  printf ("Root->right->right->left takes value 7\n");

  integer_list_t t_inorder;
  integer_list_init (&t_inorder);
  root = integer_bitree_root (&tree);
  integer_inorder (root, &t_inorder);

  printf ("List (inorder): ");
  print_integer_list (&t_inorder);

  integer_list_t t_preorder;
  integer_list_init (&t_preorder);

  integer_list_t t_postorder;
  integer_list_init (&t_postorder);

  integer_preorder (root, &t_preorder);
  integer_postorder (root, &t_postorder);

  printf ("List (preorder): ");
  print_integer_list (&t_preorder);

  printf ("List (postorder): ");
  print_integer_list (&t_postorder);

  integer_bitree_destroy (&tree);
  integer_list_destroy (&t_preorder);
  integer_list_destroy (&t_inorder);
  integer_list_destroy (&t_postorder);

  return EXIT_SUCCESS;
}
