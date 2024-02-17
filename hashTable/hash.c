#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct hash_node
{
	char *key;
	int value;
	struct hash_node *next;
} hash_node_t;
typedef struct hash_table
{
	int size;
	char **array;
} hash_table_t;
hash_table_t *create_ht(int size)
{
	hash_table_t *ht;

	if (size == '\0')
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
int hash_index(char *key, int size)
{
	// Using divion method
	int index, i, hash = 0;
	int keyLen = strlen(key);;

	for (i = 0; i < keyLen; i++)
		hash += key[i];
	index = hash % size;

	return index;
}
int main()
{
	hash_table_t *ht;
	int h_index;

	ht = create_ht(34);
	h_index = hash_index("Tobi", 10);
	printf("%d\n", h_index);
	h_index = hash_index("Bola", 29);
	printf("%d\n", h_index);
	h_index = hash_index("Toby", 15);
	printf("%d\n", h_index);
	printf("%p\n", (void *)ht);

	return (0);
}
