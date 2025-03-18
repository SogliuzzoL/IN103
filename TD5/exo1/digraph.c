#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "list.h"
#include "set.h"
#include "queue.h"

void print_graph(integer_graph_t *graph)
{
  generic_list_elmt_t *elem1 =
      generic_list_head(&(graph->adjlists));
  /* Boucle sur les elements de la liste */
  for (; elem1 != NULL; elem1 = generic_list_next(elem1))
  {
    integer_adjlist_t *tempV1 =
        (integer_adjlist_t *)generic_list_data(elem1);
    printf("Vertex %d: ", tempV1->vertex);

    generic_list_elmt_t *elem2 =
        generic_list_head(&(tempV1->adjacent));
    /* Boucle sur les elements de l'ensemble (set) */
    for (; elem2 != NULL; elem2 = generic_list_next(elem2))
    {
      integer_adjlist_elmt_t *tempV2 =
          (integer_adjlist_elmt_t *)generic_list_data(elem2);
      printf("%d->", tempV2->vertex);
    }
    printf("\n");
  }
}

void bfs(integer_graph_t *graph, int root)
{
  integer_queue_t queue;
  integer_queue_init(&queue);
  integer_queue_enqueue(&queue, root);

  integer_set_t set;
  integer_set_init(&set);
  integer_set_insert(&set, root);

  int data;
  generic_list_elmt_t *elmt;
  generic_list_elmt_t *elmt2;
  while (integer_queue_size(&queue))
  {
    integer_queue_dequeue(&queue, &data);

    elmt = generic_list_head(&graph->adjlists);
    for (; elmt != NULL; elmt = generic_list_next(elmt))
    {
      if (((integer_adjlist_t *)generic_list_data(elmt))->vertex == data)
      {
        printf("%d -> ", data);
        elmt2 = generic_list_head(&((integer_adjlist_t *)generic_list_data(elmt))->adjacent);
        for (; elmt2 != NULL; elmt2 = generic_list_next(elmt2))
        {
          int vertex = *(int *)generic_list_data(elmt2);
          if (!integer_set_is_member(&set, vertex))
          {
            printf("%d, ", vertex);
            integer_set_insert(&set, vertex);
            integer_queue_enqueue(&queue, vertex);
          }
        }
        printf("\n");
        break;
      }
    }
  }
}

int main(int argc, char **argv)
{
  integer_graph_t graph;
  integer_graph_init(&graph);

  for (int i = 1; i < 8; i++)
  {
    integer_graph_ins_vertex(&graph, i);
  }

  integer_graph_ins_edge(&graph, 1, 6, 1);

  integer_graph_ins_edge(&graph, 2, 1, 1);
  integer_graph_ins_edge(&graph, 2, 4, 1);
  integer_graph_ins_edge(&graph, 2, 5, 1);
  integer_graph_ins_edge(&graph, 2, 6, 1);
  integer_graph_ins_edge(&graph, 2, 7, 1);

  integer_graph_ins_edge(&graph, 3, 4, 1);

  integer_graph_ins_edge(&graph, 4, 5, 1);
  integer_graph_ins_edge(&graph, 4, 1, 1);

  integer_graph_ins_edge(&graph, 6, 4, 1);

  print_graph(&graph);
  printf("\n\n");

  bfs(&graph, 2);

  integer_graph_destroy(&graph);
  return EXIT_SUCCESS;
}
