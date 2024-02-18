#include "hash_tables.h"

int hash_index(char *key, unsigned long int size)
{
	unsigned long int index, hash = 0;

	while (*key != '\0')
		hash = (hash * 31) + *key++;
	index = hash % size;
	return index;
}
