#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "set.h"
#include "list.h"

int main (){

  char* str = "Salut les amis, je vous aime de tout mon coeur.";
  int len = strlen(str);

  character_set_t letters;
  character_set_init (&letters);

  for (int i = 0; i < len; i++) {
    /* keep only alphabetic characters */
    if (isalpha(str[i])) {
      /* keep only lowercase version of characters */
      character_set_insert (&letters, tolower(str[i]));
    }
  }

  /* set is an alias for list so cast to define iterator */
  character_list_t letters_l = letters;
  character_list_elmt_t *elt = character_list_head(&letters_l);
  for (; elt != character_list_tail(&letters_l); elt = character_list_next (elt)) {
    printf ("%c, ", character_list_data(elt));
  }
  printf ("%c\n", character_list_data(character_list_tail(&letters_l)));

  character_set_destroy (&letters);

  return EXIT_SUCCESS;
}
