#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

bool is_palindrome (char* str) {

  int len = strlen (str);
  character_stack_t stack;
  character_stack_init (&stack);

  int i;
  for (i = 0; i < len / 2; i++) {
    character_stack_push (&stack, str[i]);
  }
  if (len % 2 == 1) {
    /* Ne pas considerer le caractere du milieu */
    i++;
  }
  for (; i < len; i++) {
    char c;
    character_stack_pop (&stack, &c);
    if (c != str[i]) {
      character_stack_destroy (&stack);
      return false;
    }
  }
  character_stack_destroy (&stack);
  return true;
}

int main (int argc, char** argv){

  char* str = "acyca";

  bool result = is_palindrome (str);

  if (result) {
    printf ("%s is a palindrome\n", str);
  }
  else {
    printf ("%s is not a palindrome\n", str);
  }

  return EXIT_SUCCESS;
}
