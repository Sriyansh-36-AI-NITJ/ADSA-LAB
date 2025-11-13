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
        return -1;

    struct Node *temp = q->front;
    int val = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return val;
}

int isEmpty(struct Queue *q)
{
    return (q->front == NULL);
}

int front(struct Queue *q)
{
    return q->front ? q->front->data : -1;
}

void printQueue(struct Queue *q)
{
    struct Node *t = q->front;
    while (t)
    {
        printf("%d ", t->data);
        t = t->next;
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

void selectionSort(int arr[], int start, int end)
{
    for (int i = start; i < end - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < end; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

struct Queue *hybridSortAndMerge(int arr[], int n, int chunkSize)
{
    int numChunks = (n + chunkSize - 1) / chunkSize;

    printf("Sorting chunks:\n");
    struct Queue **chunkQueues = (struct Queue **)malloc(numChunks * sizeof(struct Queue *));

    for (int i = 0; i < numChunks; i++)
    {
        int start = i * chunkSize;
        int end = (start + chunkSize < n) ? start + chunkSize : n;
        selectionSort(arr, start, end);

        printf("Chunk %d sorted: ", i + 1);
        for (int j = start; j < end; j++)
            printf("%d ", arr[j]);
        printf("\n");

        chunkQueues[i] = createQueue();
        for (int j = start; j < end; j++)
            enqueue(chunkQueues[i], arr[j]);
    }

    while (numChunks > 1)
    {
        int newCount = 0;
        for (int i = 0; i < numChunks; i += 2)
        {
            if (i + 1 < numChunks)
                chunkQueues[newCount++] = mergeSortedQueues(chunkQueues[i], chunkQueues[i + 1]);
            else
                chunkQueues[newCount++] = chunkQueues[i];
        }
        numChunks = newCount;
    }

    struct Queue *finalQueue = chunkQueues[0];
    free(chunkQueues);

    return finalQueue;
}

int main()
{
    int arr[] = {42, 15, 23, 4, 16, 8, 9, 55, 0, 18};
    int n = sizeof(arr) / sizeof(arr[0]);
    int chunkSize = 3;

    printf("Original array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    struct Queue *sortedQueue = hybridSortAndMerge(arr, n, chunkSize);

    printf("\nFinal Merged Sorted Queue:\n");
    printQueue(sortedQueue);

    return 0;
}
