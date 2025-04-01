#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int lo = 0;
  int hi = 0;
  fscanf(stdin, "%d %d", &lo, &hi);
  int i = lo;
  if (i % 2)
    i++;
  for (; i <= hi; i += 2)
  {
    printf("%d\n", i);
  }
  i = hi;
  if (i % 2 == 0)
    i--;
  for (; i >= lo; i -= 2)
  {
    printf("%d\n", i);
  }

  return EXIT_SUCCESS;
}
