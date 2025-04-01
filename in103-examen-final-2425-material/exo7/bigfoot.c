#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "integer_graphalg.h"

int main(void)
{

  int size = 0;
  fscanf(stdin, "%d", &size);

  integer_graph_t graph;
  integer_graph_init(&graph);

  int s1 = 0;
  double p = 0;
  int s2 = 0;
  while (fscanf(stdin, "%d %lf %d", &s1, &p, &s2) != EOF)
  {
    integer_graph_ins_vertex(&graph, s1);
    integer_graph_ins_vertex(&graph, s2);
    integer_graph_ins_edge(&graph, s1, s2, p);
    integer_graph_ins_edge(&graph, s2, s1, p);
  }

  generic_list_t *span;
  integer_mst(&graph, &span);

  for (generic_list_elmt_t *elmt = generic_list_head(span); elmt != NULL; elmt = generic_list_next(elmt))
  {
    we_t *wEdge = generic_list_data(elmt);
    printf("[ %d --(%.1f)-- %d ], ", wEdge->source, wEdge->weight, wEdge->destination);
  }
  printf("\n");

  return 0;
}
