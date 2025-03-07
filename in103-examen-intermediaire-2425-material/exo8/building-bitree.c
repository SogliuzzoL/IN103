#include <stdlib.h>
#include <stdio.h>

#include "bitreealg.h"
#include "bitree.h"
#include "generic_queue.h"
#include "list.h"

int main(void)
{
  int height = 0;
  fscanf(stdin, "%d", &height);

  character_bitree_t tree;
  character_bitree_init(&tree);

  generic_queue_t queue;
  generic_queue_init(&queue, NULL, NULL, NULL);

  char value;
  fscanf(stdin, "\n%c", &value);
  character_bitree_ins_left(&tree, NULL, value);

  character_bitreenode_t *node = character_bitree_root(&tree);

  while ((fscanf(stdin, "\n%c", &value)) != EOF)
  {
    if (character_bitree_left(node) == NULL)
    {
      character_bitree_ins_left(&tree, node, value);
      character_bitreenode_t *newNode = character_bitree_left(node);
      generic_queue_enqueue(&queue, newNode);
    }
    else
    {
      character_bitree_ins_right(&tree, node, value);
      character_bitreenode_t *newNode = character_bitree_right(node);
      generic_queue_enqueue(&queue, newNode);
      generic_queue_dequeue(&queue, (void **)&node);
    }
  }

  character_list_t list;
  character_list_init(&list);
  character_inorder(character_bitree_root(&tree), &list);

  character_list_elmt_t *elmt = character_list_head(&list);
  while (elmt != NULL)
  {
    printf("%c", character_list_data(elmt));
    elmt = character_list_next(elmt);
  }
  printf("\n");

  character_bitree_destroy(&tree);

  return 0;
}
