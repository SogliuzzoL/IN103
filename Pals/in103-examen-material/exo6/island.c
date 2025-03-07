#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main(void)
{
  integer_graph_t graph;
  integer_graph_init(&graph);

  int size = 0;
  fscanf(stdin, "%d", &size);

  for (int i = 0; i < size; i++)
  {
    integer_graph_ins_vertex(&graph, i);
  }

  for (int i = 0; i < size; i++)
  {
    int x;
    int y;
    fscanf(stdin, "%d-%d", &x, &y);
    if (!integer_graph_is_adjacent(&graph, x, y))
    {
      printf("%d %d\n", x, y);
      integer_graph_ins_edge(&graph, x, y, 0);
      integer_graph_ins_edge(&graph, y, x, 0);
    }
  }

  integer_set_t set;
  integer_set_init(&set);
  int nbIsland = 1;

  for (int i = 0; i < size; i++)
  {
    bool newIsland = false;
    for (int j = 0; j < size; j++)
    {
      if (i != j && !integer_set_is_member(&set, i) && !integer_set_is_member(&set, j))
      {
        if (integer_graph_is_adjacent(&graph, i, j))
        {
          integer_set_insert(&set, j);
        }
        else if (!newIsland)
        {
          printf("%d %d\n", i, j);
          nbIsland++;
          newIsland = true;
        }
      }
    }
    integer_set_insert(&set, i);
  }
  printf("%d\n", nbIsland);
  return 0;
}
