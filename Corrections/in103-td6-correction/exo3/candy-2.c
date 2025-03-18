#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"

void print_graph (integer_graph_t* graph) {
  generic_list_elmt_t* elem1 =
    generic_list_head(&(graph->adjlists));
  /* Boucle sur les elements de la liste */
  for (; elem1 != NULL; elem1 = generic_list_next(elem1)) {
    integer_adjlist_t* tempV1 =
      (integer_adjlist_t*)generic_list_data(elem1);
    printf ("Vertex %d: ", tempV1->vertex);

    generic_list_elmt_t* elem2 =
      generic_list_head(&(tempV1->adjacent));
    /* Boucle sur les elements de l'ensemble (set) */
    for (; elem2 != NULL; elem2 = generic_list_next(elem2)) {
      integer_adjlist_elmt_t *tempV2 =
	(integer_adjlist_elmt_t*)generic_list_data(elem2);
      printf ("%d->", tempV2->vertex);
    }
    printf ("\n");
  }
}


int main (int argc, char** argv) {
  integer_graph_t graph;
  integer_graph_init (&graph);

  for (int i = 0; i < 10 ; i++) {
    integer_graph_ins_vertex(&graph, i);
  }
  integer_graph_ins_edge(&graph, 0, 1, 5.0);
  integer_graph_ins_edge(&graph, 0, 2, 10.0);
  integer_graph_ins_edge(&graph, 0, 3, 8.0);

  integer_graph_ins_edge(&graph, 1, 4, 7.0);
  integer_graph_ins_edge(&graph, 1, 5, 10.0);

  integer_graph_ins_edge(&graph, 2, 3, 1.0);
  integer_graph_ins_edge(&graph, 2, 4, 8.0);
  integer_graph_ins_edge(&graph, 2, 5, 2.0);

  integer_graph_ins_edge(&graph, 3, 5, 2.0);
  integer_graph_ins_edge(&graph, 3, 6, 4.0);

  integer_graph_ins_edge(&graph, 4, 7, 7.0);

  /* Nouvel arc */
  integer_graph_ins_edge(&graph, 5, 9, 7.0);

  integer_graph_ins_edge(&graph, 9, 6, 2.0);
  integer_graph_ins_edge(&graph, 9, 7, 4.0);
  integer_graph_ins_edge(&graph, 9, 8, 6.0);

  integer_graph_ins_edge(&graph, 6, 8, 6.0);

  integer_graph_ins_edge(&graph, 7, 8, 10.0);

  print_graph (&graph);
  printf ("\n\n");

  double** localflows;
  double flow;
  integer_maxflow (&graph, 0, 8, &localflows, &flow);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i != j && localflows[i][j] > 0.0) {
	printf ("%d -(%.1f)-> %d; ", i, localflows[i][j], j);
      }
    }
    printf ("\n");
  }
  printf ("flow=%f\n", flow);

  integer_graph_destroy (&graph);
  return EXIT_SUCCESS;
}
