#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bistree.h"
#include "list.h"
#include "bitreealg.h"

/* A faire un truc ici */

void init_set(set_t *s)
{
  /* A faire */
}

void destroy_set(set_t *s)
{
  /* A faire */
}

int insert_set(set_t *s, int elem)
{
  /* A faire */
  return 0;
}

int remove_set(set_t *s, int elem)
{
  /* A faire */
  return 0;
}

int size_set(set_t *s)
{
  /* A faire */
  return 0;
}

bool is_member(set_t *s, int elem)
{
  /* A faire */
  return false;
}

bool is_subset(set_t *s1, set_t *s2)
{
  /* A faire */
  return false;
}

bool is_equal(set_t *s1, set_t *s2)
{
  /* A faire */
  return false;
}

int union_set(set_t *su, set_t *s1, set_t *s2)
{
  /* A faire */
  return 0;
}

int difference_set(set_t *sd, set_t *s1, set_t *s2)
{
  /* A faire */
  return 0;
}

int intersection_set(set_t *si, set_t *s1, set_t *s2)
{
  /* A faire */
  return 0;
}

void print_set(set_t *s)
{
  generic_list_t l;
  generic_list_init(&l, NULL, NULL, NULL);
  generic_bitreenode_t *root = generic_bitree_root(s);
  generic_inorder(root, &l);

  generic_list_elmt_t *elt;
  for (elt = generic_list_head(&l);
       elt != generic_list_tail(&l);
       elt = generic_list_next(elt))
  {
    printf("%d, ", ((integer_avlnode_t *)generic_list_data(elt))->data);
  }
  printf("%d\n", ((integer_avlnode_t *)generic_list_data(generic_list_tail(&l)))->data);
}

int main()
{

  set_t s1;
  init_set(&s1);
  set_t s2;
  init_set(&s2);
  set_t su;
  init_set(&su);
  set_t sd;
  init_set(&sd);
  set_t si;
  init_set(&si);

  int size1 = 6;
  int tab1[] = {2, 4, 6, 8, 10, 12};

  int size2 = 8;
  int tab2[] = {6, 8, 10, 12, 14, 16, 18, 20};

  for (int i = 0; i < size1; i++)
  {
    insert_set(&s1, tab1[i]);
  }

  for (int i = 0; i < size2; i++)
  {
    insert_set(&s2, tab2[i]);
  }

  printf("s1 = ");
  print_set(&s1);

  printf("s2 = ");
  print_set(&s2);

  difference_set(&sd, &s1, &s2);
  printf("sd = ");
  print_set(&sd);

  union_set(&su, &s1, &s2);
  printf("su = ");
  print_set(&su);

  intersection_set(&si, &s1, &s2);
  printf("si = ");
  print_set(&si);

  if (is_subset(&si, &su))
  {
    printf("si subset of su\n");
  }

  destroy_set(&s1);
  destroy_set(&s2);
  destroy_set(&sd);
  destroy_set(&si);
  destroy_set(&su);

  return EXIT_SUCCESS;
}
