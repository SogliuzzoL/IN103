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
  /* The graph is not directed so we enter the edges in one direction
     and in the other direction */
  integer_graph_ins_edge(&graph, 0, 1, 5.0); integer_graph_ins_edge(&graph, 1, 0, 5.0);
  integer_graph_ins_edge(&graph, 0, 2, 3.0); integer_graph_ins_edge(&graph, 2, 0, 3.0);
  integer_graph_ins_edge(&graph, 0, 4, 4.0); integer_graph_ins_edge(&graph, 4, 0, 4.0);

  integer_graph_ins_edge(&graph, 1, 2, 3.0); integer_graph_ins_edge(&graph, 2, 1, 3.0);
  integer_graph_ins_edge(&graph, 1, 3, 3.0); integer_graph_ins_edge(&graph, 3, 1, 3.0);
  integer_graph_ins_edge(&graph, 1, 5, 2.0); integer_graph_ins_edge(&graph, 5, 1, 2.0);
  integer_graph_ins_edge(&graph, 1, 7, 4.0); integer_graph_ins_edge(&graph, 7, 1, 4.0);

  integer_graph_ins_edge(&graph, 2, 4, 5.0); integer_graph_ins_edge(&graph, 4, 2, 5.0);
  integer_graph_ins_edge(&graph, 2, 5, 3.0); integer_graph_ins_edge(&graph, 5, 2, 3.0);
  integer_graph_ins_edge(&graph, 2, 6, 4.0); integer_graph_ins_edge(&graph, 6, 2, 4.0);

  integer_graph_ins_edge(&graph, 3, 7, 2.0); integer_graph_ins_edge(&graph, 7, 3, 2.0);

  integer_graph_ins_edge(&graph, 4, 6, 4.0); integer_graph_ins_edge(&graph, 6, 4, 4.0);
  integer_graph_ins_edge(&graph, 4, 8, 2.0); integer_graph_ins_edge(&graph, 8, 4, 2.0);

  integer_graph_ins_edge(&graph, 5, 6, 4.0); integer_graph_ins_edge(&graph, 6, 5, 4.0);
  integer_graph_ins_edge(&graph, 5, 7, 3.0); integer_graph_ins_edge(&graph, 7, 5, 3.0);
  integer_graph_ins_edge(&graph, 5, 9, 3.0); integer_graph_ins_edge(&graph, 9, 5, 3.0);

  integer_graph_ins_edge(&graph, 6, 8, 3.0); integer_graph_ins_edge(&graph, 8, 6, 3.0);
  integer_graph_ins_edge(&graph, 6, 9, 2.0); integer_graph_ins_edge(&graph, 9, 6, 2.0);

  integer_graph_ins_edge(&graph, 7, 9, 4.0); integer_graph_ins_edge(&graph, 9, 7, 4.0);

  integer_graph_ins_edge(&graph, 8, 9, 4.0); integer_graph_ins_edge(&graph, 9, 8, 4.0);

  print_graph (&graph);
  printf ("\n\n");

  generic_list_t *span;
  integer_mst (&graph, &span);
  generic_list_elmt_t *elem = generic_list_head (span);
  for (; elem != NULL; elem = generic_list_next (elem)) {
    we_t* wEdge = generic_list_data (elem);
    printf ("[ %d --(%.1f)-- %d ], ", wEdge->source, wEdge->weight, wEdge->destination);
  }
  printf ("\n");

  generic_list_destroy (span);
  integer_graph_destroy (&graph);
  return EXIT_SUCCESS;
}
