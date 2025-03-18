#include <stdio.h>
#include <stdlib.h>

#include "integer_bistree.h"
#include "bitreealg.h"
#include "integer_list.h"

void print_avlnode_list (generic_list_t *list) {
  generic_list_elmt_t* elt = generic_list_head(list);
  for (; elt != generic_list_tail(list); elt = generic_list_next(elt)) {
    printf ("%d, ", ((integer_avlnode_t*)generic_list_data(elt))->data);
  }
  printf ("%d\n", ((integer_avlnode_t*)generic_list_data(generic_list_tail(list)))->data);
}

int max_height (generic_bitreenode_t *root) {
  int hL = 0;
  int hR = 0;
  if (generic_bitree_is_eob(root)) {
    return 0;
  }

  if (generic_bitree_left (root) != NULL) {
    hL = max_height (generic_bitree_left (root)) + 1;
  }

  if (generic_bitree_right (root) != NULL) {
    hR = max_height (generic_bitree_right (root)) + 1;
  }

  return hL > hR ? hL : hR;
}

void add_node(integer_bitree_t* tree, integer_bitreenode_t* current, int elem){

  int current_data = integer_bitree_data(current);

  if (elem != current_data) {
    if (elem <= current_data){
      if (integer_bitree_left (current) == NULL) {
	integer_bitree_ins_left (tree, current, elem);
      }
      else {
	add_node (tree, integer_bitree_left(current), elem);
      }
    } else {
      if (integer_bitree_right (current) == NULL) {
	integer_bitree_ins_right (tree, current, elem);
      } else {
	add_node (tree, integer_bitree_right(current), elem);
      }
    }
  }
}

void print_integer_list (integer_list_t *list) {
  integer_list_elmt_t* elt = integer_list_head(list);
  for (; elt != integer_list_tail(list); elt = integer_list_next(elt)) {
    printf ("%d, ", integer_list_data(elt));
  }
  printf ("%d\n", integer_list_data(integer_list_tail(list)));
}

int main (){
  int size = 9;
  int tab[] = {32689, 31320, 22915, 15617, 16203, 4458, 255, 20940, 12335}; /* Problem with negative numbers -16203 and below => check rotations! */

  integer_bistree_t avl;
  integer_bistree_init (&avl);

  for (int i = 0; i < size; i++) {
    integer_bistree_insert (&avl, tab[i]);
    printf ("insert %d => root is %d\n", tab[i],
	    ((integer_avlnode_t*)generic_bitree_data(generic_bitree_root(&avl)))->data);
  }

  generic_list_t sorted_avl;
  generic_list_init (&sorted_avl, NULL, NULL, NULL);
  generic_bitreenode_t* root_avl = generic_bitree_root (&avl);
  generic_inorder (root_avl, &sorted_avl);

  print_avlnode_list (&sorted_avl);

  /* Partie ABR fait maison */
  integer_bitree_t abr;
  integer_bitree_init (&abr);

  /* Gestion de la racine */
  integer_bitree_ins_left(&abr , NULL, tab[0]);
  printf ("insert %d => root is %d\n", tab[0], integer_bitree_data(integer_bitree_root (&abr)));
  integer_bitreenode_t* root_abr = integer_bitree_root (&abr);
  /* Pour les autres valeurs */
  for (int i = 1; i < size; i++) {
    add_node (&abr, root_abr, tab[i]);
    printf ("insert %d => root is %d\n", tab[i], integer_bitree_data(integer_bitree_root (&abr)));
  }

  integer_list_t sorted_abr;
  integer_list_init (&sorted_abr);
  integer_inorder (root_abr, &sorted_abr);
  print_integer_list (&sorted_abr);

  /* Comparaison des hauteurs d'arbres */
  printf ("Hauteurs: AVL = %d and ABR = %d\n",
	  max_height (root_avl), max_height((generic_bitreenode_t*)root_abr));

  integer_bistree_destroy(&avl);
  integer_bitree_destroy(&abr);
  generic_list_destroy (&sorted_avl);
  integer_list_destroy (&sorted_abr);

  return EXIT_SUCCESS;
}
