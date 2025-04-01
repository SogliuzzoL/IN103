#include <stdio.h>
#include <stdlib.h>

int gain(int g, int x)
{
  return g * x;
}

int main(int argc, char **argv)
{

  int c = 0;
  int cpt = 1;
  while (fscanf(stdin, "%d", &c) != EOF)
  {
    printf("%d\n", c * cpt);
    cpt ++;
  }

  return 0;
}
