#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *front;
    struct Node *rear;
};

struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct Queue *q, int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(struct Queue *q)
{
    if (q->front == NULL)
        return -1; // empty

    struct Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return value;
}

int isEmpty(struct Queue *q)
{
    return (q->front == NULL);
}

int front(struct Queue *q)
{
    if (q->front == NULL)
        return -1;
    return q->front->data;
}

void printQueue(struct Queue *q)
{
    struct Node *temp = q->front;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Queue *mergeSortedQueues(struct Queue *q1, struct Queue *q2)
{
    struct Queue *merged = createQueue();

    while (!isEmpty(q1) && !isEmpty(q2))
    {
        if (front(q1) <= front(q2))
            enqueue(merged, dequeue(q1));
        else
            enqueue(merged, dequeue(q2));
    }

    while (!isEmpty(q1))
        enqueue(merged, dequeue(q1));

    while (!isEmpty(q2))
        enqueue(merged, dequeue(q2));

    return merged;
}

int main()
{
    struct Queue *q1 = createQueue();
    struct Queue *q2 = createQueue();

    enqueue(q1, 1);
    enqueue(q1, 4);
    enqueue(q1, 7);

    enqueue(q2, 2);
    enqueue(q2, 3);
    enqueue(q2, 8);

    printf("Queue 1: ");
    printQueue(q1);
    printf("Queue 2: ");
    printQueue(q2);

    struct Queue *merged = mergeSortedQueues(q1, q2);

    printf("\nMerged Sorted Queue: ");
    printQueue(merged);

    return 0;
}
