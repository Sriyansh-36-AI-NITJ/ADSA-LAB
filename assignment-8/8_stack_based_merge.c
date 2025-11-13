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
    if (!q->front)
        return -1;
    struct Node *temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (!q->front)
        q->rear = NULL;
    free(temp);
    return val;
}

int front(struct Queue *q)
{
    if (!q->front)
        return -1;
    return q->front->data;
}

int isEmptyQueue(struct Queue *q)
{
    return (q->front == NULL);
}

void printQueue(struct Queue *q)
{
    struct Node *temp = q->front;
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Queue *mergeSortedQueues(struct Queue *q1, struct Queue *q2)
{
    struct Queue *merged = createQueue();
    while (!isEmptyQueue(q1) && !isEmptyQueue(q2))
    {
        if (front(q1) <= front(q2))
            enqueue(merged, dequeue(q1));
        else
            enqueue(merged, dequeue(q2));
    }
    while (!isEmptyQueue(q1))
        enqueue(merged, dequeue(q1));
    while (!isEmptyQueue(q2))
        enqueue(merged, dequeue(q2));
    return merged;
}

struct StackNode
{
    struct Queue *q;
    struct StackNode *next;
};

struct Stack
{
    struct StackNode *top;
};

struct Stack *createStack()
{
    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    s->top = NULL;
    return s;
}

void push(struct Stack *s, struct Queue *q)
{
    struct StackNode *node = (struct StackNode *)malloc(sizeof(struct StackNode));
    node->q = q;
    node->next = s->top;
    s->top = node;
}

struct Queue *pop(struct Stack *s)
{
    if (!s->top)
        return NULL;
    struct StackNode *temp = s->top;
    struct Queue *q = temp->q;
    s->top = temp->next;
    free(temp);
    return q;
}

int isEmptyStack(struct Stack *s)
{
    return s->top == NULL;
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

struct Queue *stackBasedMerge(int arr[], int n, int chunkSize)
{
    int numChunks = (n + chunkSize - 1) / chunkSize;
    struct Stack *s = createStack();

    printf("Sorting and pushing chunks to stack:\n");

    for (int i = 0; i < numChunks; i++)
    {
        int start = i * chunkSize;
        int end = (start + chunkSize < n) ? start + chunkSize : n;

        selectionSort(arr, start, end);
        struct Queue *q = createQueue();
        for (int j = start; j < end; j++)
            enqueue(q, arr[j]);

        printf("Chunk %d sorted: ", i + 1);
        printQueue(q);

        push(s, q);
    }

    printf("\nMerging using stack:\n");
    while (!isEmptyStack(s) && s->top->next != NULL)
    {
        struct Queue *q1 = pop(s);
        struct Queue *q2 = pop(s);

        struct Queue *merged = mergeSortedQueues(q1, q2);
        printf("Merged two queues: ");
        printQueue(merged);

        push(s, merged);
    }

    return pop(s);
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

    struct Queue *result = stackBasedMerge(arr, n, chunkSize);

    printf("\nFinal merged sorted queue:\n");
    printQueue(result);

    return 0;
}
