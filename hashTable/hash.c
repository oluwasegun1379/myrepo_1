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
	hash_node_t **array;
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
	int c;
	int index = 5380;

	while (c = *key++)
		index = (((index << 5) + index) + c) % size;
	return index;
}
int set_ht(hash_table_t *ht, char *key, int value)
{
   	int index;
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
	new->next = NULL;

	new->next = ht->array[index];
	ht->array[index] = new;

	return 1;
}

int main()
{
	hash_table_t *ht;
	hash_node_t *current;

	ht = create_ht(5);
	printf("%p\n", (void *)ht);

	set_ht(ht, "Segun", 25);
	set_ht(ht, "John", 30);
	set_ht(ht, "Tobi", 15);
	set_ht(ht, "Ayo", 22);
	set_ht(ht, "Richard", 37);
	set_ht(ht, "AZ", 27);
	set_ht(ht, "Kiddo", '\0');
	set_ht(ht, "Fawaz", 28);
	set_ht(ht, "Shola", 29);
	set_ht(ht, "Blessin", 20);
	set_ht(ht, "Kareem", 26);
	set_ht(ht, "Segun", 25);
	set_ht(ht, "Lolade", 17);
	set_ht(ht, "Samsom", 15);
	set_ht(ht, "Wick", 35);
	set_ht(ht, "Merlin", 24);

	for (int i = 0; i < ht->size; i++)
	{
		current = ht->array[i];
		while (current != NULL)
		{
			printf("%d-+-%s->(%d)\n", i, current->key, current->value);
			current = current->next;
		}
	}

	return (0);
}
