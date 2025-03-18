#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"
#include "set.h"
#include "stack.h"


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

double traversabilite (int terrain) {

  double cout = 0.0;
  /* printf ("%s: argument=%d\n", __func__, terrain); */

  switch (terrain) {
  case 2:
    /* Route */
    cout = 1.0;
    break;
  case 3:
    /* Pont */
    cout = 1.0;
    break;
  case 4:
    /* Prairie */
    cout = 2.0;
    break;
  case 5:
    /* Chemin forestier */
    cout = 3.0;
    break;
  case 6:
    /* Desert */
    cout = 4.0;
    break;
  case 7:
    /* Foret */
    cout = 4.0;
    break;
  case 8:
    /* Marecage */
    cout = 5.0;
    break;
  default:
    /* Pour abime, riviere, montagne */
    cout = 1e308;
    break;
  }

  return cout;
}

int buildGraph (integer_graph_t *graph, char* filename) {
  FILE* fd = fopen (filename, "r");
  if (fd == NULL) {
    fprintf (stderr, "Ne peux pas ouvrir le fichier %s\n", filename);
    return 0;
  }

  int dimension;
  fscanf (fd, "%d", &dimension);
  printf ("Dimension de la carte est %d\n", dimension);

  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension+1; j++) {
      char c  = fgetc(fd);
      if (! isspace(c)) { 	/* Note: le saut de ligne est en debut */
	/* double cout = traversabilite ( (int) (c - 48)); */

	/* TODO */

      }
    }
  }

  fclose(fd);
  return dimension;
}

int main (int argc, char** argv) {

  if (argc != 2) {
    printf ("Usage: %s carte.txt\n", argv[0]);
    return EXIT_FAILURE;
  }

  integer_graph_t graph;
  integer_graph_init (&graph);

  /* int dimension = buildGraph (&graph, argv[1]); */

  print_graph (&graph);

  /* TODO */

  integer_graph_destroy (&graph);

  return EXIT_SUCCESS;
}
