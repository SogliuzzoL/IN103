#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int left = 0;
  int right = 0;
  int incr = 0;
  fscanf(stdin, "%d %d %d", &left, &incr, &right);

  if (left > right && incr > 0)
  {
    printf("needs negative increment\n");
  }
  else if (left < right && incr < 0)
  {
    printf("needs positive increment\n");
  }
  else if (incr == 0 && left != right)
  {
    printf("incorrect increment value\n");
  }
  else
  {
    if (left < right)
    {
      for (int i = left; i <= right; i++)
      {
        printf("%d\n", i);
      }
    }
    else
    {
      for (int i = left; i >= right; i--)
      {
        printf("%d\n", i);
      }
    }
  }

  return EXIT_SUCCESS;
}
