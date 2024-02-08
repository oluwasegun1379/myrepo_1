#include <stdio.h>

typedef struct listint_s
{
    int n;
    struct listint_s *next;
} listint_t;

void print_array(const int *array, size_t size);
void print_list(const listint_t *list);

int main()
{
    const int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);

    listint_t node5 = {5, NULL};
    listint_t node4 = {4, &node5};
    listint_t node3 = {3, &node4};
    listint_t node2 = {2, &node3};
    listint_t node1 = {1, &node2};
    listint_t *list = &node1;

    print_array(array, size);
    print_list(list);

    return 0;
}

/**
 * print_array - Prints an array of integers
 *
 * @array: The array to be printed
 * @size: Number of elements in @array
 */
void print_array(const int *array, size_t size)
{
    size_t i = 0;
    while (i < size)
    {
        if (i > 0)
            printf(", ");
        printf("%d", array[i]);
        ++i;
    }
    printf("\n");
}

/**
 * print_list - Prints a linked list of integers
 *
 * @list: The list to be printed
 */
void print_list(const listint_t *list)
{
    int i = 0;
    while (list)
    {
        if (i > 0)
            printf(", ");
        printf("%d", list->n);
        ++i;
        list = list->next;
    }
    printf("\n");
}

