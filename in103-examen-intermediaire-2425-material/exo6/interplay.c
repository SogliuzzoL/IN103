#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "graph.h"

int main(void)
{
  int size = 0;
  fscanf(stdin, "%d", &size);

  character_list_t list;
  character_list_init(&list);

  char elmt;
  while (fscanf(stdin, "\n%c", &elmt) != EOF)
  {
    character_list_ins_next(&list, character_list_tail(&list), elmt);
  }

  for (int i = 0; i < size; i++)
  {
    character_list_elmt_t *elmtList = character_list_head(&list);
    for (int j = 0; j < i; j++)
    {
      elmtList = character_list_next(elmtList);
    }
    char data;
    while (elmtList != NULL)
    {
      data = character_list_data(elmtList);
      printf("%c", data);
      for (int j = 0; j < size; j++)
      {
        elmtList = character_list_next(elmtList);
        if (elmtList == NULL)
        {
          break;
        }
      }
    }
    printf("\n");
  }

  return 0;
}
