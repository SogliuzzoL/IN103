#include <stdio.h>
#include <stdlib.h>

void *malloc(size_t t)
{
    printf("%zu\n", t);
    return NULL;
}