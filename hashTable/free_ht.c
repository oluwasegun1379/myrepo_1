#include "hash_tables.h"
void free_ht(hash_table_t *ht)
{
	int i;
	hash_node_t *current, *temp;

	for (i = 0; i < ht->size; i++)
	{
		current = ht->array[i];
		while (current != NULL)
		{
			temp = current;
			current = current->next;
			free(temp->key);
			free(temp);
		}
	}
	free(ht->array);
	free(ht);
}
