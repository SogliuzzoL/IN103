#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <integer_uf.h>

typedef struct edge_
{
  int cell1;
  int cell2;
} edge_t;

int main(int argc, char **argv)
{

  srand(time(NULL));

  int widthMaze = 10;
  int totalCell = widthMaze * widthMaze;

  int nbEdge = 2 * widthMaze * (widthMaze - 1);
  printf("nbEdge = %d\n", nbEdge);

  /* Nombre total de murs est: 2 * totalCell * (totalCell - 1) */
  edge_t edges[nbEdge];
  edge_t maze[nbEdge];

  /* Preparation: liste tous les murs possibles */
  int cpt = 0;
  for (int i = 0; i < widthMaze; i++)
  {
    for (int j = 0; j < widthMaze; j++)
    {

      int index = i * widthMaze + j; /* Indice de la case */

      int south = (i + 1) * widthMaze + j;
      int east = i * widthMaze + j + 1;

      if (south >= 0 && south < totalCell)
      {
        edge_t temp;
        temp.cell1 = index;
        temp.cell2 = south;
        edges[cpt++] = temp;
      }

      if (east >= 0 && east < totalCell && east != (i + 1) * widthMaze)
      {
        edge_t temp;
        temp.cell1 = index;
        temp.cell2 = east;
        edges[cpt++] = temp;
      }
    }
  }

  int k = 0;
  printf("All edges = ");
  for (k = 0; k < nbEdge - 1; k++)
  {
    printf("(%d, %d), ", edges[k].cell1, edges[k].cell2);
  }
  printf("(%d, %d)\n", edges[k].cell1, edges[k].cell2);

  /* Debut de l'algorithme de generation du labyrinthe */
  integer_uf_t uf;
  integer_uf_init(&uf, totalCell);
  for (int i = 0; i < totalCell; i++)
  {
    integer_uf_add_element(&uf, i);
  }

  int rNumber;
  int len = nbEdge - 1;
  edge_t edge;
  int nbMur = 0;

  printf("M edges = ");
  while (integer_uf_components(&uf) > 1)
  {
    rNumber = rand() % len;
    edge = edges[rNumber];
    edges[rNumber] = edges[len];
    edges[len] = edge;
    len--;

    if (!integer_uf_are_connected(&uf, edge.cell1, edge.cell2))
      integer_uf_union(&uf, edge.cell1, edge.cell2);
    else
    {
      maze[nbMur++] = edge;
      printf("(%d, %d), ", maze[nbMur - 1].cell1, maze[nbMur - 1].cell2);
    }
  }
  printf("\nL not used edges = ");
  for (int i = 0; i < len; i++)
  {
    printf("(%d, %d), ", edges[i].cell1, edges[i].cell2);
  }
  printf("\nlen = %d, nbMur = %d, Total = %d\n", len, nbMur, len + nbMur);

  integer_uf_destroy(&uf);

  return EXIT_SUCCESS;
}
