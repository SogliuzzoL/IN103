#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "integer_graphalg.h"
#include "list.h"
#include "set.h"

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

bool check(integer_graph_t *graph, int start, int place)
{
  integer_list_t ordered;
  integer_list_init(&ordered);
  integer_dfs(graph, start, &ordered);
  integer_list_elmt_t *elmt = integer_list_head(&ordered);
  for (; elmt != NULL; elmt = integer_list_next(elmt))
  {
    if (integer_list_data(elmt) == place)
    {
      return true;
    }
    
    if (integer_list_data(elmt) == 1)
    {
      return false;
    }
    
  }

  return false;
}

int main(int argc, char **argv)
{
  int N;
  int v1;
  int v2;
  int Q;
  int order;
  int start;
  int place;
  bool result;
  fscanf(stdin, "%d\n", &N);

  integer_graph_t graph;
  integer_graph_init(&graph);

  for (int i = 0; i < N - 1; i++)
  {
    fscanf(stdin, "%d %d\n", &v1, &v2);
    integer_graph_ins_vertex(&graph, v1);
    integer_graph_ins_vertex(&graph, v2);
    integer_graph_ins_edge(&graph, v1, v2, 0);
    integer_graph_ins_edge(&graph, v2, v1, 0);
  }

  print_graph(&graph);

  fscanf(stdin, "%d", &Q);
  for (int i = 0; i < Q; i++)
  {
    fscanf(stdin, "\n%d %d %d", &order, &start, &place);
    if (!order)
    {
      result = check(&graph, place, start);
    }
    else
      result = check(&graph, start, place);
    
    if (result)
    {
      printf("YES\n");
    }
    else printf("NO\n");
    
  }

  return EXIT_SUCCESS;
}
