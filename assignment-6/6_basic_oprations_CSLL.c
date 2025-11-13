
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
struct Node *last = NULL;

void insertAtBeginning(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    if (!last)
    {
        last = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = last->next;
        last->next = newNode;
    }
}

void insertAtEnd(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    if (!last)
    {
        last = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = last->next;
        last->next = newNode;
        last = newNode;
    }
}

void display()
{
    if (!last)
        return;
    struct Node *temp = last->next;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != last->next);
    printf("\n");
}

int main()
{
    printf("Inserting node(10) at End:");
    insertAtEnd(10);
    display();

    printf("Inserting node(11) at End:");
    insertAtEnd(11);
    display();

    printf("Inserting node(5) at beginning:");
    insertAtBeginning(5);
    display();

    printf("Inserting node(20) at end");
    insertAtEnd(20);
    display();
    return 0;
}
