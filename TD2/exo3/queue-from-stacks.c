#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct myqueue
{
  integer_stack_t in;
  integer_stack_t out;
} myqueue_t;

/* ************************************************************ */
/*  Fonctions à mettre ne oeuvre  */
/* ************************************************************ */
void init(myqueue_t *queue)
{
  integer_stack_init(&queue->in);
  integer_stack_init(&queue->out);
}

void destroy(myqueue_t *queue)
{
  integer_stack_destroy(&queue->in);
  integer_stack_destroy(&queue->out);
}

int enqueue(myqueue_t *queue, int value)
{
  return integer_stack_push(&queue->out, value);
}

int shift_stacks(integer_stack_t *in, integer_stack_t *out)
{
  int element;
  while (integer_stack_size(in) > 0)
  {
    if (integer_stack_pop(in, &element))
      return -1;
    if (integer_stack_push(out, element))
      return -1;
  }
  return 0;
}

int dequeue(myqueue_t *queue, int *value)
{
  if (shift_stacks(&queue->in, &queue->out))
    return -1;
  return integer_stack_pop(&queue->out, value);
}

int size(myqueue_t *queue)
{
  return integer_stack_size(&queue->in) + integer_stack_size(&queue->out);
}
/* ************************************************************ */

int main()
{

  int tab[3] = {1, 2, 3};
  myqueue_t queue;

  init(&queue);

  for (int i = 0; i < 3; i++)
  {
    int code = enqueue(&queue, tab[i]);
    if (code != 0)
    {
      perror("Erreur enqueue\n");
      destroy(&queue);
      return -1;
    }
  }

  printf("Dequeue = ");
  fflush(stdout);
  for (int i = 0; i < 3; i++)
  {
    int elt;
    int code = dequeue(&queue, &elt);
    if (code != 0)
    {
      perror("Erreur dequeue\n");
    }
    printf("%d, ", elt);
  }
  printf("\n");

  destroy(&queue);

  return EXIT_SUCCESS;
}
