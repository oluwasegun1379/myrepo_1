#ifndef HASH_TABLES_H
#define HASH_TABLES_H

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


hash_table_t *create_ht(int size);
int hash_index(char *key, unsigned long int size);
int set_ht(hash_table_t *ht, char *key, int value);
void print_ht(hash_table_t *ht);
void free_ht(hash_table_t *ht);
void look_for(hash_table_t *ht, char *key);

#endif /* HASH_TABLES_H */
