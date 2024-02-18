#include "hash_tables.h"

int set_ht(hash_table_t *ht, char *key, int value)
{
   	int i, index;
	hash_node_t *new;

	if (ht == NULL || key == NULL || *key == '\0')
		return 0;
	index = hash_index(key, ht->size);
	
	new = malloc(sizeof(hash_node_t));
	if (new == NULL)
		return 0;
	new->key = strdup(key); // duplicated the string.
	if (new->key == NULL)
	{
		free(new);
		return 0;
	}
	new->value = value;

	new->next = ht->array[index];
	ht->array[index] = new;

	return 1;
}

