#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "integer_graphalg.h"
#include "list.h"
#include "set.h"

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

bool check (integer_graph_t* graph, int start, int place) {
  integer_list_t ordered_dfs;
  integer_list_init (&ordered_dfs);
  integer_dfs (graph, start, &ordered_dfs);
  integer_list_elmt_t* elem = integer_list_head (&ordered_dfs);
  for (; elem != NULL; elem = integer_list_next (elem)) {
    int n = integer_list_data (elem);
    if (n == place) {
      integer_list_destroy (&ordered_dfs);
      return true;
    }
  }
  integer_list_destroy (&ordered_dfs);
  return false;
}


int main (int argc, char** argv) {
  integer_graph_t graph_away;
  integer_graph_init (&graph_away);
  integer_graph_t graph_towards;
  integer_graph_init (&graph_towards);

  int nbHouses;
  fscanf (stdin, "%d", &nbHouses);

  for (int i = 1; i <= nbHouses ; i++) {
    integer_graph_ins_vertex(&graph_away, i);
    integer_graph_ins_vertex(&graph_towards, i);
  }

  for (int i = 1; i <= nbHouses - 1; i++) {
    int start, end;
    fscanf (stdin, "%d %d", &start, &end);
    integer_graph_ins_edge(&graph_away, start, end, 0.0);
    integer_graph_ins_edge(&graph_towards, end, start, 0.0);
  }

  /* print_graph (&graph_away); */
  /* printf ("\n\n"); */
  /* print_graph (&graph_towards); */
  /* printf ("\n\n"); */

  int nbQueries;
  fscanf (stdin, "%d", &nbQueries);

  bool result = false;
  for (int i = 1; i <= nbQueries; i++) {
    int direction;
    int hidePlace;
    int start;
    fscanf (stdin, "%d %d %d", &direction, &hidePlace, &start);
    if (direction == 1) { // move away
      result = check (&graph_away, start, hidePlace);
    }
    else { // direction == 0 : move towards
      result = check (&graph_towards, start, hidePlace);
    }

    if (result == true) {
      printf ("YES\n");
    }
    else {
      printf ("NO\n");
    }
  }

  integer_graph_destroy (&graph_away);
  integer_graph_destroy (&graph_towards);
  return EXIT_SUCCESS;
}
