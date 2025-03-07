#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "list.h"
#include "set.h"

/* Hyopothese : la liste ne contient que des caracteres minuscules et
   des espaces ou symboles de ponctuation (qu'il faut ignorer) */
bool is_pangram(character_list_t *str, int *sizePangram)
{
  character_list_elmt_t *elmt = character_list_head(str);
  character_set_t set;
  character_set_init(&set);
  while (elmt != NULL)
  {
    char data = character_list_data(elmt);
    if (islower(data))
    {
      character_set_insert(&set, data);
      *sizePangram += 1;
    }
    elmt = character_list_next(elmt);
  }
  int setSize = character_set_size(&set);
  character_set_destroy(&set);

  if (setSize == 26)
  {
    return true;
  }

  return false;
}

int main(int argc, char **argv)
{

  character_list_t lstr;
  character_list_init(&lstr);

  char c = '0';
  while (fscanf(stdin, "%c", &c) != EOF)
  {
    if (c != '\n')
    {
      character_list_ins_next(&lstr, character_list_tail(&lstr), c);
    }
  }

  int sizePangram = 0;
  bool result = is_pangram(&lstr, &sizePangram);

  if (result)
  {
    printf("YES(%d)", sizePangram);
  }
  else
  {
    printf("NO");
  }
  printf("\n");

  character_list_destroy(&lstr);

  return EXIT_SUCCESS;
}
