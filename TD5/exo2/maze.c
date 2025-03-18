#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "integer_uf.h"
#include "graph.h"
#include "queue.h"
#include "list.h"
#include "set.h"

typedef struct edge_ {
  int cell1;
  int cell2;
} edge_t;

void generate_maze (int dimension, edge_t** paths, int* size) {

  srand(time(NULL));

  int widthMaze = dimension;
  int totalCell = widthMaze * widthMaze;

  int nbEdge = 2 * widthMaze * (widthMaze - 1);

  edge_t edges[nbEdge];
  edge_t freePaths[nbEdge];

  /* Creation of the list of all edges (i.e. walls) */
  int cpt = 0;
  for (int i = 0; i < widthMaze; i++) {
    for (int j = 0; j < widthMaze; j++) {

      int index = i * widthMaze + j; /* Case index  */

      int south = (i + 1) * widthMaze + j;
      int east = i * widthMaze + j + 1;

      if (south >= 0 && south < totalCell) {
	edge_t temp;
	temp.cell1 = index;
	temp.cell2 = south;
	edges[cpt++] = temp;
      }

      if (east >= 0 && east < totalCell && east != (i+1)*widthMaze) {
	edge_t temp;
	temp.cell1 = index;
	temp.cell2 = east;
	edges[cpt++] = temp;
      }
    }
  }
  int k = 0;

  /* Create data structure for gathering all elements of the union-find */
  integer_uf_t dset;
  integer_uf_init (&dset, totalCell);

  for (int i = 0; i < totalCell; i++) {
    integer_uf_add_element (&dset, i);
  }

  int nbFreePaths = 0;   		/* For tree building */

  /* Generate maze from union-find and the list of edges */
  int len = nbEdge-1;

  int r;
  int cptWall = 0;
  while (integer_uf_components(&dset) > 1) {
    /* Random pick of an edge i.e., random pick of an index in the tab of edges */
    r = rand() % len;

    /* Handling random edges considering less and less edges i.e. a
       smaller tab of edges */
    /* Each time an edge is selected, we swicth it with the latest
       one in the tab and decrease the size of the tab */
    edge_t e = edges[r];
    edges[r] = edges[len];
    edges[len] = e;
    len--;
    printf ("Selected edge = (%d, %d) -- %d\n", e.cell1, e.cell2, r);

    if (!integer_uf_are_connected (&dset, e.cell1, e.cell2)) {
      freePaths[nbFreePaths++] = e;
      integer_uf_union (&dset, e.cell1, e.cell2); /* The egde
						     (i.e. the wall)
						     is removed */
    }
  }

  *paths = malloc ((nbFreePaths) * sizeof(edge_t));
  *size = nbFreePaths;
  for (k = 0; k < nbFreePaths; k++) {
    (*paths)[k] = freePaths[k];
  }

  integer_uf_destroy(&dset);
}

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

void vers_la_sortie (integer_graph_t* graph, int entree, int sortie) {
  /* TODO */
}

int main (int argc, char** argv) {

  int dimension = 4;
  int nbCases = dimension * dimension;
  edge_t* path = NULL;
  int len;

  generate_maze (dimension, &path, &len);

  integer_graph_t graph;
  integer_graph_init (&graph);

  /* TODO Construire le graphe non oriente */

  printf ("\n\n");
  print_graph (&graph);
  printf ("\n\n");

  /* TODO: appliquer vers_la_sortie */

  integer_graph_destroy (&graph);

  return EXIT_SUCCESS;
}
