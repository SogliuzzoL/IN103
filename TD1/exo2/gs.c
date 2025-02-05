#include <stdlib.h>
#include <stdio.h>

#include "gs.h"

void gram_schmidt(int n, int size, matrix_t vectors)
{

  free(vectors[0]);
  vectors[0] = normalize(size, vectors[0]);

  for (int i = 1; i < n; i++)
  {
    vector_t tempI = vectors[i];
    for (int j = 0; j < i; j++)
    {
      vector_t tempJ = vectors[j];
      double t = dot(size, tempI, tempJ);
      tempI = axby(size, tempI, tempJ, 1.0, -t);
    }
    free(vectors[i]);
    vectors[i] = normalize(size, tempI);
  }
}
