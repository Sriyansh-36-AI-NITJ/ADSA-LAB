#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Node *mergeSortedLists(struct Node *list1, struct Node *list2)
{
    struct Node dummy;
    struct Node *tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data <= list2->data)
        {
            tail->next = list1;
            list1 = list1->next;
        }
        else
        {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL)
        tail->next = list1;
    if (list2 != NULL)
        tail->next = list2;

    return dummy.next;
}

int main()
{
    struct Node *list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);

    struct Node *list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);

    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    struct Node *merged = mergeSortedLists(list1, list2);

    printf("\nMerged Sorted List: ");
    printList(merged);

    return 0;
}
