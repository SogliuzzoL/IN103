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

  int lenFreePaths = 0;   		/* For tree building */

  /* Generate maze from union-find and the list of edges */
  int len = nbEdge-1;

  int r;
  //  int cptWall = 0;
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
      freePaths[lenFreePaths++] = e;
      integer_uf_union (&dset, e.cell1, e.cell2); /* The egde
						     (i.e. the wall)
						     is removed */
    }
  }

  *paths = malloc ((lenFreePaths) * sizeof(edge_t));
  *size = lenFreePaths;
  for (k = 0; k < lenFreePaths; k++) {
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
  integer_queue_t path;
  integer_queue_init (&path);
  integer_queue_t queue;
  integer_queue_init (&queue);
  integer_set_t set;
  integer_set_init (&set);

  integer_set_insert (&set, entree);
  integer_queue_enqueue (&queue, entree);

  bool trouve = false;

  while (integer_queue_size (&queue) > 0 && trouve == false) {
    int vertex;
    integer_queue_dequeue (&queue, &vertex);

    generic_list_elmt_t* lelem = generic_list_head (&(graph->adjlists));
    for (; lelem != NULL; lelem = generic_list_next (lelem)) {
      integer_adjlist_t* node = (integer_adjlist_t*) generic_list_data (lelem);
      if (node->vertex == vertex) {
	if (node->vertex == sortie) {
	  trouve = true;
	  integer_queue_enqueue (&path, node->vertex);
	}
	else {
	  generic_list_elmt_t* lelem2 = generic_list_head (&(node->adjacent));
	  for (; lelem2 != NULL; lelem2 = generic_list_next (lelem2)) {
	    integer_adjlist_elmt_t* child =
	      (integer_adjlist_elmt_t*) generic_list_data (lelem2);

	    if (!integer_set_is_member (&set, child->vertex)) {
	      integer_set_insert (&set, child->vertex);
	      integer_queue_enqueue (&queue, child->vertex);
	      integer_queue_enqueue (&path, node->vertex);
	    }
	  }
	}
      }
    }
  }
  if (trouve == false) {
    printf ("Il n'y a pas de chemin entre %d et %d\n", entree, sortie);
  }
  else {
    integer_list_elmt_t* elem = integer_list_head (&path);
    int pred = integer_list_data(elem);
    printf ("%d -> ", pred);
    elem = integer_list_next (elem);
    for (; elem != NULL; elem = integer_list_next (elem)) {
      int d = integer_list_data(elem);
      if (d != pred) {
	pred = d;
	printf ("%d -> ", d);
      }
    }
    printf ("\n");
  }
}

int main (int argc, char** argv) {

  int dimension = 4;
  int nbCases = dimension * dimension;
  edge_t* path = NULL;
  int len;

  generate_maze (dimension, &path, &len);

  integer_graph_t graph;
  integer_graph_init (&graph);

  for (int i = 0; i < nbCases; i++) {
    integer_graph_ins_vertex(&graph, i);
  }

  for (int k = 0; k < len; k++) {
    printf ("(%d, %d) - ", path[k].cell1, path[k].cell2);
    integer_graph_ins_edge(&graph, path[k].cell1, path[k].cell2, 0.0);
    // integer_graph_ins_edge(&graph, path[k].cell2, path[k].cell1, 0.0);
  }
  printf ("\n\n");
  print_graph (&graph);
  printf ("\n\n");

  printf ("Le chemin de longueur minimal allant de %d vers %d est : ", 0, nbCases-1);
  vers_la_sortie (&graph, 0, nbCases-1);

  integer_graph_destroy (&graph);

  return EXIT_SUCCESS;
}
