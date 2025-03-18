#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <integer_uf.h>

typedef struct edge_ {
  int cell1;
  int cell2;
} edge_t;


int main (int argc, char** argv) {

  srand(time(NULL));

  int widthMaze = 10;
  int totalCell = widthMaze * widthMaze;

  int nbEdge = 2 * widthMaze * (widthMaze - 1);
  printf ("nbEdge = %d\n", nbEdge);

  /* Nombre total de murs est: 2 * widthMaze * (widthMaze - 1) */
  edge_t edges[nbEdge];
  edge_t maze[nbEdge];

  /* Preparation: liste tous les murs possibles */
  int cpt = 0;
  for (int i = 0; i < widthMaze; i++) {
    for (int j = 0; j < widthMaze; j++) {

      int index = i * widthMaze + j; /* Indice de la case */

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
  printf ("All edges = ");
  for (k = 0; k < nbEdge - 1; k++) {
    printf ("(%d, %d), ", edges[k].cell1, edges[k].cell2);
  }
  printf ("(%d, %d)\n", edges[k].cell1, edges[k].cell2);

  /* Debut de l'algorithme de generation du labyrinthe */
  integer_uf_t dset;
  integer_uf_init (&dset, totalCell);

  for (int i = 0; i < totalCell; i++) {
    integer_uf_add_element (&dset, i);
  }

  /* Boucle principale de l'algorithme */
  int len = nbEdge-1;
  int r;
  int cptWall = 0;
  while (integer_uf_components(&dset) > 1) {
    r = rand() % len;

    edge_t e = edges[r];

    edges[r] = edges[len];
    edges[len] = e;
    len--;

    if (!integer_uf_are_connected (&dset, e.cell1, e.cell2)) {
      integer_uf_union (&dset, e.cell1, e.cell2);
    }
    else {
      maze[cptWall++] = e;
    }
  }

  /* Affichage du resultat */
  printf ("Maze edges = ");
  k = 0;
  for (k = 0; k < cptWall-1; k++) {
    printf ("(%d, %d), ", maze[k].cell1, maze[k].cell2);
  }
  if (cptWall > 1) {
    printf ("(%d, %d)\n", maze[k].cell1, maze[k].cell2);
  }
  else {
    printf ("\n");
  }

  printf ("Remainder edges = ");
  k = 0;
  for (k = 0; k < len; k++) {
    printf ("(%d, %d), ", edges[k].cell1, edges[k].cell2);
  }
  printf ("(%d, %d)\n", edges[k].cell1, edges[k].cell2);


  /* Nettoyage */
  integer_uf_destroy(&dset);

  return EXIT_SUCCESS;
}
