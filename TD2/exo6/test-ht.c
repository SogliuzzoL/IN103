#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic_hashtable.h"
#include "generic_list.h"

int myCompareKey(const void *data1, const void *data2)
{
  char *elem1 = (char *)data1;
  char *elem2 = (char *)data2;
  return strcmp((char *)elem1, (char *)elem2);
}

void *myBuild(const void *data)
{
  generic_ht_elmt_t *orig = (generic_ht_elmt_t *)data;
  generic_ht_elmt_t *elem = malloc(sizeof(generic_ht_elmt_t));
  if (elem == NULL)
  {
    return NULL;
  }
  elem->key = malloc(sizeof(char) * (strlen(orig->key)));
  strncpy(elem->key, orig->key, strlen(orig->key));
  elem->value = orig->value;

  return elem;
}

int main()
{

  int code;
  int size = 7;
  char *tabKey[] = {"pomme", "poire", "ananas", "avocat", "orange", "banane", "cerise"};
  long int tabValue[] = {1, -2, 12, 3, -1, 202, -2};
  generic_ht_t ht;

  generic_hashtable_init(&ht, myCompareKey, myBuild, NULL);

  // Insertion des éléments
  for (int i = 0; i < size; i++)
  {
    code = generic_hashtable_insert(&ht, (void *)tabKey[i], (void *)tabValue[i]);
    if (code == -1)
    {
      perror("Memory allocation problem while inserting\n");
      return EXIT_FAILURE;
    }
  }

  code = generic_hashtable_insert(&ht, (void *)tabKey[2], (void *)2345);
  if (code == -1)
  {
    perror("Memory allocation problem while inserting\n");
    return EXIT_FAILURE;
  }

  // Affichage
  for (int i = 0; i < MAXELEM; i++)
  {
    if (ht.table[i] != NULL)
    {
      printf("table[%d] = %p\n", i, ht.table[i]);
      generic_ht_elmt_t *elem = generic_list_data(generic_list_head(ht.table[i]));
      printf("\t(%s, %ld)\n", (char *)elem->key, (long int)elem->value);
    }
  }

  int cpt = 0;
  do
  {
    if (generic_hashtable_contains(&ht, (void *)tabKey[2]))
    {
      printf("la table contient des ananas\n");
    }
    else
    {
      printf("la table ne contient pas des ananas\n");
    }

    generic_ht_elmt_t *elm = generic_hashtable_remove(&ht, (void *)tabKey[2]);
    if (elm != NULL)
    {
      printf("Removed: (%s, %ld)\n", (char *)elm->key, (long int)elm->value);
    }

  } while (++cpt < 3);

  generic_hashtable_update(&ht, (void *)tabKey[6], (void *)123456);

  // Affichage
  for (int i = 0; i < MAXELEM; i++)
  {
    if (ht.table[i] != NULL)
    {
      printf("table[%d] = %p\n", i, ht.table[i]);
      generic_ht_elmt_t *elem = generic_list_data(generic_list_head(ht.table[i]));
      printf("\t(%s, %ld)\n", (char *)elem->key, (long int)elem->value);
    }
  }

  generic_hashtable_destroy(&ht);

  return EXIT_SUCCESS;
}
