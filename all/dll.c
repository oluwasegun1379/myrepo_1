#include <stdio.h>
#include <stdlib.h>

struct node
{
   int data;
   struct node* next;
   struct node* prev;
};

struct node* head = NULL;

void create(int x)
{
   struct node* new = (struct node*)malloc(sizeof(struct node));
   if (new == NULL)
   {
      return;
   }

   new->data = x;
   new->next = NULL;
   new->prev = NULL;

   if (head == NULL)
   {
      head = new;
   }
   else
   {
      struct node* temp = head;
      while (temp->next != NULL)
      {
         temp = temp->next;
      }
      temp->next = new;
      new->prev = temp;
   }
}

void print()
{
   struct node* temp = head;
   while (temp != NULL)
   {
      printf("---> %d\n", temp->data);
      temp = temp->next;
   }
}

void freed()
{
   struct node* temp = head;
   while (temp != NULL)
   {
      struct node* next_node = temp->next;
      free(temp);
      temp = next_node;
   }
   head = NULL;  // Reset head to NULL after freeing all nodes
}

int main()
{
   create(2);
   create(4);
   create(6);

   print();
   freed();
}
