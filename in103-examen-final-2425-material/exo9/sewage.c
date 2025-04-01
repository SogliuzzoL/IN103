#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "graphalg.h"
#include "stack.h"

int main(int argc, char **argv)
{
	int n;
	int m;
	int value;

	integer_graph_t graph;
	integer_graph_init(&graph);

	fscanf(stdin, "%d %d\n", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			fscanf(stdin, "%d", &value);
			if (value)
			{
				integer_graph_ins_vertex(&graph, i);
				integer_graph_ins_vertex(&graph, j);
				integer_graph_ins_edge(&graph, i, j, value);
			}
		}
		fscanf(stdin, "%d\n", &value);
		if (value)
		{
			integer_graph_ins_vertex(&graph, i);
			integer_graph_ins_vertex(&graph, n);
			integer_graph_ins_edge(&graph, i, n, value);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		printf("Vertex %d: ", i);

		int distance_m;
		int distance_n;

		generic_list_t *paths;
		integer_shortest(&graph, i, &paths);

		int *parents = malloc((2 * n * 2 * n) * sizeof(int));
		if (parents == NULL)
		{
			generic_list_destroy(paths);
			integer_graph_destroy(&graph);
			return EXIT_FAILURE;
		}

		generic_list_elmt_t *elem = generic_list_head(paths);
		for (; elem != NULL; elem = generic_list_next(elem))
		{
			ed_t *v = generic_list_data(elem);
			parents[v->vertex] = v->parent;
			if (v->vertex == n)
				distance_n = v->distance;
			if (v->vertex == m)
				distance_m = v->distance;
		}

		int u = m;
		integer_stack_t stack_m;
		integer_stack_init(&stack_m);
		while (u != -1)
		{
			integer_stack_push(&stack_m, u);
			u = parents[u];
		}

		u = n;
		integer_stack_t stack_n;
		integer_stack_init(&stack_n);
		while (u != -1)
		{
			integer_stack_push(&stack_n, u);
			u = parents[u];
		}

		int stackSize_m = integer_stack_size(&stack_m);
		int stackSize_n = integer_stack_size(&stack_n);
		if (distance_n > distance_m)
		{
			for (int i = 0; i < stackSize_m; i++)
			{
				integer_stack_pop(&stack_m, &value);
				printf("%d->", value);
			}
		}
		else
		{
			for (int i = 0; i < stackSize_n; i++)
			{
				integer_stack_pop(&stack_n, &value);
				printf("%d->", value);
			}
		}

		printf("\n");
	}

	return EXIT_SUCCESS;
}
