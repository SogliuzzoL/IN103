#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "integer_graphalg.h"
#include "list.h"
#include "set.h"
#include "queue.h"

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

int greedyColoring (integer_graph_t* graph, int** colors) {

  return 0;
}

int main (int argc, char** argv) {
  integer_graph_t graph;
  integer_graph_init (&graph);

  for (int i = 0; i < 5 ; i++) {
    integer_graph_ins_vertex(&graph, i);
  }
  integer_graph_ins_edge(&graph, 0, 1, 0.0);
  integer_graph_ins_edge(&graph, 1, 0, 0.0);

  integer_graph_ins_edge(&graph, 0, 2, 0.0);
  integer_graph_ins_edge(&graph, 2, 0, 0.0);

  integer_graph_ins_edge(&graph, 1, 2, 0.0);
  integer_graph_ins_edge(&graph, 2, 1, 0.0);

  integer_graph_ins_edge(&graph, 1, 3, 0.0);
  integer_graph_ins_edge(&graph, 3, 1, 0.0);

  integer_graph_ins_edge(&graph, 2, 3, 0.0);
  integer_graph_ins_edge(&graph, 3, 2, 0.0);

  integer_graph_ins_edge(&graph, 3, 4, 0.0);
  integer_graph_ins_edge(&graph, 4, 3, 0.0);

  print_graph (&graph);
  printf ("\n\n");

  int* colors;
  greedyColoring(&graph, &colors);

  printf("Affichage\n");
  for (int i = 0; i < integer_graph_vcount (&graph); i++) {
    printf ("[%d] = %d\n", i, colors[i]);
  }

  free(colors);
  integer_graph_destroy (&graph);
  return EXIT_SUCCESS;
}
