#include "hash_tables.h"
hash_table_t *create_ht(int size)
{
	hash_table_t *ht;

	if (size == 0)
		return NULL;

	ht = malloc(sizeof(hash_table_t));
	if (ht == NULL)
		return NULL;

	ht->size = size;
	ht->array = malloc(sizeof(hash_table_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return NULL;
	}

	for (int i = 0; i < size; i++)
		ht->array[i] = NULL;

	return ht;
}
