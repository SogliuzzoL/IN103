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

  //  printf ("Dimension de la carte est %d\n", dimension);

  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension+1; j++) {
      char c  = fgetc(fd);
      if (! isspace(c)) { 	/* Note: le saut de ligne est en debut */
	/* fprintf (stderr, "(%d,%d): %c\n", i, j-1, c); */
	double cout = traversabilite ( (int) (c - 48));
	int nord = (2 * i) * 2 * dimension + 2 * (j-1) + 1;
	int sud = (2 * i + 2) * 2 * dimension + 2 * (j-1) + 1;
	int est = (2 * i + 1) * 2 * dimension + 2 * (j-1) + 2;
	int ouest = (2 * i + 1) * 2 * dimension + 2 * (j-1);

	printf ("\\node[draw,ellipse] at (%d, -%d) (s%d) {%d};\n", (2*j+1), (2 * i),  nord, nord);
	printf ("\\node[draw,ellipse] at (%d, -%d) (s%d) {%d};\n", (2*j+1), (2 * i + 2),  sud, sud);
	printf ("\\node[draw,ellipse] at (%d, -%d) (s%d) {%d};\n", (2*j+2), (2 * i + 1),  est, est);
	printf ("\\node[draw,ellipse] at (%d, -%d) (s%d) {%d};\n", (2*j), (2 * i + 1),  ouest, ouest);


	integer_graph_ins_vertex (graph, nord);
	integer_graph_ins_vertex (graph, sud);
	integer_graph_ins_vertex (graph, est);
	integer_graph_ins_vertex (graph, ouest);

	if(cout < 1e308) {
	  printf ("\\draw[-] (s%d) -- (s%d);\n",  nord, est);
	  printf ("\\draw[-] (s%d) -- (s%d);\n",  nord, ouest);
	  printf ("\\draw[-] (s%d) -- (s%d);\n",  sud, est);
	  printf ("\\draw[-] (s%d) -- (s%d);\n",  sud, ouest);

	  integer_graph_ins_edge (graph, nord, est, cout);
	  integer_graph_ins_edge (graph, est, nord, cout);
	  integer_graph_ins_edge (graph, nord, ouest, cout);
	  integer_graph_ins_edge (graph, ouest, nord, cout);
	  integer_graph_ins_edge (graph, sud, est, cout);
	  integer_graph_ins_edge (graph, est, sud, cout);
	  integer_graph_ins_edge (graph, sud, ouest, cout);
	  integer_graph_ins_edge (graph, ouest, sud, cout);
	}
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

  int dimension = buildGraph (&graph, argv[1]);

  //print_graph (&graph);

  /* Sommet a l'est de la derniere case de la derniere ligne */
  int start = (2 * 9 + 1) * 2 * dimension + (2 * 9 + 2);
  /* Sommet au nord de la derniere case de la premiere ligne */
  int end = (0 * 9) * 2 * dimension + (2 * 9 + 1);

  generic_list_t *paths;
  integer_shortest (&graph, start, &paths);

  /* On recherche le chemin */
  int* parents = malloc ((2*dimension*2*dimension)*sizeof(int));
  if (parents == NULL) {
    generic_list_destroy (paths);
    integer_graph_destroy (&graph);
    return EXIT_FAILURE;
  }

  generic_list_elmt_t *elem = generic_list_head (paths);
  for (; elem != NULL; elem = generic_list_next (elem)) {
    ed_t* v = generic_list_data (elem);
    parents[v->vertex] = v->parent;
  }

  int pred = -1;
  int u = end;
  while (u != -1) {
    /* int x = u / (2 * dimension); */
    /* int y = u - 2 * x * dimension; */
    /* x = (x - 1) / 2; */
    /* y = (y - 1) / 2; */
    /* printf ("(%d, %d) <- ", x, y); */
    /* printf ("%d <- ", u); */
    pred = u;
    u = parents[u];
    if (u != -1) {
      printf ("\\draw[-, red, very thick] (s%d) -- (s%d);\n", pred, u);
    }
  }
  /* printf ("\n"); */


  generic_list_destroy (paths);
  integer_graph_destroy (&graph);

  return EXIT_SUCCESS;
}
