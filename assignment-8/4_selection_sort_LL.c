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

void swapNodes(struct Node **head_ref, struct Node *prevX, struct Node *currX,
               struct Node *prevY, struct Node *currY)
{
    if (currX == currY)
        return;

    if (prevX != NULL)
        prevX->next = currY;
    else
        *head_ref = currY;

    if (prevY != NULL)
        prevY->next = currX;
    else
        *head_ref = currX;

    struct Node *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

void selectionSortList(struct Node **head_ref)
{
    struct Node *i, *j, *min;
    struct Node *prev_i = NULL;
    struct Node *prev_j;
    struct Node *prev_min;

    for (i = *head_ref; i != NULL && i->next != NULL; prev_i = i, i = i->next)
    {
        min = i;
        prev_min = prev_i;

        for (prev_j = i, j = i->next; j != NULL; prev_j = j, j = j->next)
        {
            if (j->data < min->data)
            {
                min = j;
                prev_min = prev_j;
            }
        }

        if (min != i)
            swapNodes(head_ref, prev_i, i, prev_min, min);

        printf("List after iteration: ");
        printList(*head_ref);
    }
}

int main()
{
    struct Node *head = createNode(64);
    head->next = createNode(25);
    head->next->next = createNode(12);
    head->next->next->next = createNode(22);
    head->next->next->next->next = createNode(11);

    printf("Original list: ");
    printList(head);

    selectionSortList(&head);

    printf("\nSorted list: ");
    printList(head);

    return 0;
}
