#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "stack.h"

int main(void)
{
  int size = 0;
  fscanf(stdin, "%d", &size);

  character_list_t list;
  character_list_init(&list);

  character_stack_t stack;
  character_stack_init(&stack);

  char value = '0';

  while (fscanf(stdin, "%c", &value) != EOF)
  {
    if (value != '\n')
    {
      character_stack_push(&stack, value);
    }
  }

  int stackSize = character_stack_size(&stack);
  for (int i = 0; i < stackSize; i++)
  {
    character_stack_pop(&stack, &value);
    character_list_ins_next(&list, character_list_tail(&list), value);
  }

  for (int i = 0; i < size; i++)
  {
    character_list_elmt_t *elmt = character_list_head(&list);

    for (int j = i; j < size - 1; j++)
    {
      elmt = character_list_next(elmt);
    }

    while (elmt != NULL)
    {
      printf("%c", elmt->data);
      for (int k = 0; k < size; k++)
      {
        elmt = character_list_next(elmt);
        if (elmt == NULL)
          break;
      }
    }
    printf("\n");
  }

  return 0;
}
