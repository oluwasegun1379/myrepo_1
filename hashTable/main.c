#include "hash_tables.h"

int main()
{
	hash_table_t *ht;
	int selection;

	ht = create_ht(10);
	printf("Enter a number to perform the task\n");
	printf("1-> Print out the current table\n2-> Change the size of current table\n3-> Add a new key to table\n4-> Look for a key\n");
	scanf("%d", &selection);
	if (selection == 1)
	{
		goto next;
	}
	else if (selection == 2)
	{
		int new_size;
		printf("Enter the new size you want: ");
		scanf("%d", &new_size);
		ht = create_ht(new_size);
	}
	else if (selection == 3)
	{
		int status = 1;
		while (status)
		{
			char key[50];
			int value;
			printf("Enter the key(Name): ");
			scanf("%s", key);
			printf("Enter the Value(Age): ");
			scanf("%d", &value);
			set_ht(ht, key, value);
			printf("Enter 0 to stop add key, 1 to continue\n");
			scanf("%d", &status);
		}
	}
	next:
	set_ht(ht, "Segun", 25);
	set_ht(ht, "John", 30);
	set_ht(ht, "Tobi", 15);
	set_ht(ht, "Ayo", 22);
	set_ht(ht, "Richard", 37);
	set_ht(ht, "AZ", 27);
	set_ht(ht, "Kiddo", 0);
	set_ht(ht, "Fawaz", 28);
	set_ht(ht, "Shola", 29);
	set_ht(ht, "Blessin", 20);
	set_ht(ht, "Kareem", 26);
	set_ht(ht, "Segun", 25);
	set_ht(ht, "Lolade", 17);
	set_ht(ht, "Samsom", 15);
	set_ht(ht, "Wick", 35);
	set_ht(ht, "Merlin", 24);

	if (selection == 4)
	{
		char key[50];
		printf("Enter the key(Name) to find: ");
		scanf("%s", key);
		look_for(ht, key);
	}
	print_ht(ht);
	look_for(ht, "Segun");
	free_ht(ht);

	return (0);
}
