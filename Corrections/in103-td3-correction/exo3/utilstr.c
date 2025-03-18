#include <stdlib.h>
#include <string.h>

/* Shall define a new function to fit the specification with void* */
int compare_str (const void *a, const void *b) {
  const char* sa = a;
  const char* sb = b;
  return strcmp (sa, sb);
}

/* Shall define a new function to fit the specification with void* */
void* build_str (const void *data) {
  const char* sdata = data;
  int len = strlen(data);
  char *dest = malloc((len+1) * sizeof(char)); /* Do not forget the '\0' value */
  /* By default strncpy return a pointer on dest */
  return strncpy (dest, sdata, len+1); /* Do not forget the '\0' value */
}
