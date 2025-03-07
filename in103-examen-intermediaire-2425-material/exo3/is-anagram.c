#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "list.h"
#include "stack.h"

bool is_anagram(character_list_t *str1, character_list_t *str2)
{
  character_stack_t stack;
  character_stack_init(&stack);
  char data;
  char value;

  character_list_elmt_t *elmt = character_list_head(str1);
  while (elmt != NULL)
  {
    data = character_list_data(elmt);
    character_stack_push(&stack, data);
    elmt = character_list_next(elmt);
  }

  elmt = character_list_head(str2);
  while (elmt != NULL)
  {
    character_stack_pop(&stack, &data);
    value = character_list_data(elmt);

    if (data != value)
    {
      return false;
    }
    elmt = character_list_next(elmt);
  }

  if (character_stack_size(&stack))
  {
    return false;
  }

  character_stack_destroy(&stack);

  return true;
}

int main(int argc, char **argv)
{

  character_list_t lstr1;
  character_list_init(&lstr1);

  char c = '0';
  while (fscanf(stdin, "%c", &c) != EOF)
  {
    if (c == '*')
    {
      break;
    }
    if (c != '\n')
    {
      character_list_ins_next(&lstr1, character_list_tail(&lstr1), c);
    }
  }

  character_list_t lstr2;
  character_list_init(&lstr2);
  while (fscanf(stdin, "%c", &c) != EOF)
  {
    if (c != '\n')
    {
      character_list_ins_next(&lstr2, character_list_tail(&lstr2), c);
    }
  }

  bool result = is_anagram(&lstr1, &lstr2);

  if (result)
  {
    printf("OUI\n");
  }
  else
  {
    printf("NON\n");
  }

  character_list_destroy(&lstr1);
  character_list_destroy(&lstr2);

  return EXIT_SUCCESS;
}
