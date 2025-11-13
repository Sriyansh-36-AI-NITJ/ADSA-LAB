#include <stdio.h>

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void partialSelectionSort(int arr[], int n, int k)
{
    int i, j, min_idx, temp;

    if (k > n)
        k = n;

    for (i = 0; i < k; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;

        // printf("After iteration %d: ", i + 1);
        // printArray(arr, n);
    }
}

int main()
{
    int arr[] = {29, 10, 14, 37, 14, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    printf("Original array: ");
    printArray(arr, n);

    partialSelectionSort(arr, n, k);

    printf("Arr after partial selection sort (first %d elements sorted): ", k);
    printArray(arr, n);

    return 0;
}
