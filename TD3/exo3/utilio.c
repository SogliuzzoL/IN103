#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *trimspace(char *s)
{
  int l = strlen(s);
  if (l == 0)
  {
    return "";
  }

  while (isspace(s[l - 1]))
    --l;
  while (*s && isspace(*s))
    ++s, --l;

  return strndup(s, l);
}

char **csv_to_array(char *str, int nbfields)
{
  char **fields = malloc(nbfields * sizeof(char *));
  char *str2 = trimspace(strdup(str));
  char *str_token = strtok(str2, ";");
  int i = 0;
  while (str_token != NULL)
  {
    fields[i] = strdup(str_token);
    // On demande le token suivant.
    str_token = strtok(NULL, ";");
    i++;
  }
  return fields;
}

char *command_to_string(char *command)
{
  /* printf ("Enter %s\n", __func__); */
  FILE *pipe = popen(command, "r");
  if (pipe == NULL)
  {
    return NULL;
  }
  char str[1000];
  fgets(str, 1000, pipe);
  pclose(pipe);

  return strdup(str);
}

int command_to_int(char *command)
{
  /* printf ("Enter %s with command:\"%s\"\n", __func__, command); */
  FILE *pipe = popen(command, "r");
  if (pipe == NULL)
  {
    return 0;
  }
  char str[100];
  if (fgets(str, 100, pipe) != NULL)
  {
    /* printf ("result fgets = %s\n", str); */
  }
  else
  {
    printf("result fgets ERROR\n");
  }
  pclose(pipe);

  return atoi(str);
}
