#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"

bool is_palindrome (char* str) {
  /* TODO */
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
