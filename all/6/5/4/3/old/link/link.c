#include <stdlib.h>
#include <stdio.h>

struct node
{
	int data;
	struct node *next;
};

int main()
{
	struct node *head = NULL;
	struct node *nodeA, *nodeB, *nodeC, *nodeD, *tmp;

	nodeA = malloc(sizeof(struct node));
	nodeB = malloc(sizeof(struct node));
	nodeC = malloc(sizeof(struct node));
	nodeD = malloc(sizeof(struct node));
	
	head = nodeA;
	nodeA->data = 18;
	nodeA->next = nodeB;
	nodeB->data = 20;
	nodeB->next = nodeC;
	nodeC->data = 30;
	nodeC->next = nodeD;
	nodeD->data = 40;
	nodeD->next = NULL;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	putchar('\n');
}
