#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

  int c = 0;
  fscanf(stdin, "%d", &c);
  int result = 2 * c;
  if (result < 0)
  {
    printf("%d\n", 2147483647);
  }
  else
    printf("%d\n", result);

  return EXIT_SUCCESS;
}
