#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct
{
	char name[MAX_NAME];
	int age;
}person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
	int length = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;
	for (int i = 0; i < length; i++)
	{
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}

	return (hash_value);
}


void init_hash_table()
{
	for (int i = 0; i < TABLE_SIZE; i++)
		hash_table[i] = NULL;
	//table is empty now!
}

bool hash_table_insert(person *p)
{
	if (p == NULL)
		return (false);
	int index = hash(p->name);
	if (hash_table[index] != NULL)
		return (false);
	hash_table[index] = p;

	return (true);
}

void print_table()
{
	printf("Start\n");
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (hash_table[i] == NULL)
			printf("\t%i\t---\n", i);
		else
			printf("\t%i\t%s\n", i, hash_table[i]->name);
	}
	printf("End\n");
}
int main()
{
	init_hash_table();

	person jacob = {.name = "Jacob", .age = 25};
	person job = {.name = "Job", .age = 24};
	person Cynthia = {.name = "Cynthia", .age = 20};
	person Gabriel = {.name = "Gabriel", .age = 22};
	person Jack = {.name = "Jack", .age = 30};

	hash_table_insert(&jacob);
	hash_table_insert(&job);
	hash_table_insert(&Cynthia);
	hash_table_insert(&Gabriel);
	hash_table_insert(&Jack);

	print_table();
	/*printf("Jacob => %u\n", hash("jacob"));
	printf("Job => %u\n", hash("job"));
	printf("Jack => %u\n", hash("jack"));
	printf("Segun => %u\n", hash("Segun"));
	printf("Kiddo => %u\n", hash("Kiddo"));
	printf("Sufiat => %u\n", hash("Sufiat"));*/
	return (0);
}
