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

  for (int i = 0; i < 12 ; i++) {
    integer_graph_ins_vertex(&graph, i);
  }
  integer_graph_ins_edge(&graph, 1, 6, 1.0);
  integer_graph_ins_edge(&graph, 1, 7, 1.0);

  integer_graph_ins_edge(&graph, 2, 7, 1.0);

  integer_graph_ins_edge(&graph, 3, 8, 1.0);
  integer_graph_ins_edge(&graph, 3, 9, 1.0);
  integer_graph_ins_edge(&graph, 3, 10, 1.0);

  integer_graph_ins_edge(&graph, 4, 7, 1.0);
  integer_graph_ins_edge(&graph, 4, 10, 1.0);

  integer_graph_ins_edge(&graph, 5, 8, 1.0);

  /* Super source */
  for (int i = 1; i <= 5; i++) {
    integer_graph_ins_edge(&graph, 0, i, 1.0);
  }

  /* Super puits */
  for (int i = 6; i <= 10; i++) {
    integer_graph_ins_edge(&graph, i, 11, 1.0);
  }

  print_graph (&graph);
  printf ("\n\n");

  double** localflows;
  double flow;
  integer_maxflow (&graph, 0, 11, &localflows, &flow);
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 12; j++) {
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
