#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct myqueue_ {
  integer_stack_t in;
  integer_stack_t out;
} myqueue_t;

void init (myqueue_t *queue) {
  integer_stack_init (&(queue->in));
  integer_stack_init (&(queue->out));
}

void destroy (myqueue_t *queue) {
  integer_stack_destroy(&(queue->in));
  integer_stack_destroy(&(queue->out));
}

int enqueue (myqueue_t *queue, int value) {
  return integer_stack_push (&(queue->in), value);
}

int shift_stacks (integer_stack_t *in, integer_stack_t *out) {
  if (integer_stack_size (out) == 0) {
    int elt;
    while (integer_stack_size(in) > 0) {
      integer_stack_pop(in, &elt);
      integer_stack_push(out, elt);
    }
  }
  return 0;
}

int dequeue (myqueue_t *queue, int *value) {
  shift_stacks (&(queue->in), &(queue->out));
  return integer_stack_pop (&(queue->out), value);
}

int size (myqueue_t *queue) {
  return integer_stack_size(&(queue->in)) + integer_stack_size (&(queue->out));
}

int main (){

  int tab[3] = { 1, 2, 3 };
  myqueue_t queue;

  init (&queue);

  for (int i = 0; i < 3; i++) {
   int code = enqueue (&queue, tab[i]);
   if (code != 0) {
     perror ("Erreur enqueue\n");
     destroy(&queue);
     return -1;
   }
  }

  printf ("Dequeue = ");fflush(stdout);
  for (int i = 0; i < 3; i++) {
    int elt;
    int code = dequeue (&queue, &elt);
    if (code != 0) {
      perror ("Erreur dequeue\n");
    }
    printf ("%d, ", elt);
  }
  printf ("\n");

  destroy(&queue);


  return EXIT_SUCCESS;
}
