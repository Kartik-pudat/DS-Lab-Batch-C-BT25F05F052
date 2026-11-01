/*
 * Quick Sort - program in C
 *
 * Quick Sort is a divide and conquer algorithm:
 *   1. Choose a pivot element (here: the LAST element of the sub-array).
 *   2. Partition the array so that elements smaller than the pivot come
 *      before it and elements greater than the pivot come after it.
 *   3. Recursively apply quick sort to the left and right parts.
 *
 * Time : O(n log n) best/average, O(n^2) worst (already sorted input
 *        with last-element pivot)
 * Space: O(log n) recursion stack on average
 */

#include <stdio.h>

#define MAX 100

long comparisons = 0;
long swaps = 0;

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Partition (Lomuto scheme):
 * Places the pivot (arr[high]) at its correct sorted position and
 * returns that position's index.
 */
int partition(int arr[], int low, int high, int n) {
    int pivot = arr[high];
    int i = low - 1;                 /* boundary of the "smaller" region */

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            if (i != j) {
                swap(&arr[i], &arr[j]);
                swaps++;
            }
        }
    }

    if (i + 1 != high) {
        swap(&arr[i + 1], &arr[high]);   /* put pivot in its final place */
        swaps++;
    }

    printf("Pivot = %-4d placed at index %d -> ", pivot, i + 1);
    displayArray(arr, n);

    return i + 1;
}

void quickSort(int arr[], int low, int high, int n) {
    if (low < high) {
        int p = partition(arr, low, high, n);

        quickSort(arr, low, p - 1, n);    /* sort left of pivot  */
        quickSort(arr, p + 1, high, n);   /* sort right of pivot */
    }
}

int main() {
    int arr[MAX], n;

    printf("=== Quick Sort ===\n");
    do {
        printf("Enter number of elements (1 to %d): ", MAX);
        if (scanf("%d", &n) != 1) {
            printf("Invalid input!\n");
            return 1;
        }
    } while (n < 1 || n > MAX);

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input!\n");
            return 1;
        }
    }

    printf("\nOriginal array: ");
    displayArray(arr, n);
    printf("\nPartition steps:\n");

    quickSort(arr, 0, n - 1, n);

    printf("\nSorted array  : ");
    displayArray(arr, n);
    printf("Comparisons = %ld, Swaps = %ld\n", comparisons, swaps);

    return 0;
}