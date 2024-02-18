#include "hash_tables.h"
void print_ht(hash_table_t *ht)
{
	int i;
	hash_node_t *current;
	
	printf("Hash Index ---- Key ---- Value\n");
	for (i = 0; i < ht->size; i++)
	{
		current = ht->array[i];
		while (current != NULL)
		{
			printf("%d-----+-----(%s)------>%d\n", i, current->key, current->value);
			current = current->next;
		}
	}
}
