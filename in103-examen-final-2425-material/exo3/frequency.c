#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "list.h"

int main(int argc, char **argv)
{

  character_list_t lstr1;
  character_list_init(&lstr1);

  char c = '0';
  while (fscanf(stdin, "%c", &c) != EOF)
  {
    character_list_ins_next(&lstr1, character_list_tail(&lstr1), c);
  }

  for (int i = ' '; i < 'z'; i++)
  {
    int compte = 0;
    for (character_list_elmt_t *elmt = character_list_head(&lstr1); elmt != NULL; elmt = character_list_next(elmt))
    {
      if (elmt->data == i)
      {
        compte++;
      }
    }
    if (compte)
    {
      printf("%c:%d\n", i, compte);
    }
  }

  character_list_destroy(&lstr1);

  return EXIT_SUCCESS;
}
