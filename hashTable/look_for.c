#include "hash_tables.h"

void look_for(hash_table_t *ht, char *key)
{
	unsigned long int index = hash_index(key, ht->size);
	hash_node_t *current;

	current = ht->array[index];
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			printf("   HashIndex  Key    \n");
			printf("Found: %lu----(%s)--->%d\n", index, key, current->value);
			return;
		}
		current = current->next;
	}
	printf("Not Found!\n");
}
