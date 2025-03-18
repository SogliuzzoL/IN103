#include <stdio.h>
#include <string.h>
#include "generic_hashtable.h"

/* Hash for strings */
/* unsigned long hash_function(char* str) */
/* { */
/*     unsigned long i = 0; */

/*     for (int j = 0; str[j]; j++) */
/*         i += str[j]; */

/*     return i % CAPACITY; */
/* } */

int hashFunction (void* key) {
  long int temp = (long int) key;
  return (int) (temp % MAXELEM);
}

void generic_hashtable_init (generic_ht_t* ht,
			     int (*compare) (const void *data1, const void *data2),
			     void* (*build)(const void *data),
			     void (*destroy)(void *data)) {
  for (int i = 0; i < MAXELEM; i++) {
    ht->table[i] = NULL;
  }
  ht->compare = compare;
  ht->build = build;
  ht->destroy = destroy;
  ht->size = 0;
}

void generic_hashtable_destroy (generic_ht_t* ht) {
  for (int i = 0; i < MAXELEM; i++) {
    if (ht->table[i] != NULL) {
      generic_list_destroy (ht->table[i]);
    }
  }
  ht->size=0;
}

int generic_hashtable_insert (generic_ht_t* ht, void* key, void* value) {
  int index = hashFunction (key);

  if (ht->table[index] == NULL) {
    generic_list_t* temp = malloc (sizeof(generic_list_t));
    if (temp == NULL) {
      return -1;
    }
    generic_list_init (temp, ht->compare, ht->build, NULL);
    ht->table[index] = temp;
  }

  generic_ht_elmt_t* elem = malloc (sizeof(generic_ht_elmt_t));
  if (elem == NULL) {
    return -1;
  }
  elem->key = key;
  elem->value = value;

  int code = generic_list_ins_next (ht->table[index], NULL, (void*) elem);
  ht->size++;
  return code;
}

generic_ht_elmt_t* generic_hashtable_remove (generic_ht_t* ht, void* key) {
  int index = hashFunction (key);

  if (ht->table[index] == NULL) {
    return NULL;
  }

  generic_list_elmt_t* iterator = generic_list_head(ht->table[index]);
  generic_list_elmt_t* previous = NULL;
  while (iterator != NULL) {
    generic_ht_elmt_t* data = generic_list_data (iterator);
    if (ht->compare(data -> key, key) == 0) {
      generic_list_rem_next (ht->table[index], previous, (void*) &data);
      data = ht->build(data);
      if (generic_list_size(ht->table[index]) == 0) {
	generic_list_destroy (ht->table[index]);
	ht->table[index] = NULL;
      }
      return data;
    }
    previous = iterator;
    iterator = generic_list_next (iterator);
  }

  return NULL;
}

generic_ht_elmt_t* generic_hashtable_lookfor (generic_ht_t* ht, void* key) {
  int index = hashFunction (key);

  if (ht->table[index] == NULL) {
    return NULL;
  }

  generic_list_elmt_t* iterator = generic_list_head(ht->table[index]);
  for (; iterator != NULL; iterator = generic_list_next (iterator)) {
    generic_ht_elmt_t* data = generic_list_data (iterator);
    if (ht->compare(data -> key, key) == 0) {
      return data;
    }
  }

  return NULL;
}

int generic_hashtable_update (generic_ht_t* ht, void* key, void* value) {
  int index = hashFunction (key);

  if (ht->table[index] == NULL) {
    return generic_hashtable_insert (ht, key, value);
  }

  generic_list_elmt_t* iterator = generic_list_head(ht->table[index]);
  for (; iterator != NULL; iterator = generic_list_next (iterator)) {
    generic_ht_elmt_t* data = generic_list_data (iterator);
    if (ht->compare(data -> key, key) == 0) {
      data -> value = value;
      return 0;
    }
  }

  return generic_hashtable_insert (ht, key, value);
}

bool generic_hashtable_contains (generic_ht_t* ht, void* key) {
  int index = hashFunction (key);

  if (ht->table[index] == NULL) {
    return false;
  }

  generic_list_elmt_t* iterator = generic_list_head(ht->table[index]);
  for (; iterator != NULL; iterator = generic_list_next (iterator)) {
    generic_ht_elmt_t* data = generic_list_data (iterator);
    if (ht->compare(data -> key, key) == 0) {
      return true;
    }
  }

  return false;
}

int generic_hashtable_size (generic_ht_t* ht) {
  return ht->size;
}
