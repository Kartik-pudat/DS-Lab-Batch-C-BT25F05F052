/*
 * Insertion Sort - program in C
 *
 * Insertion Sort builds the sorted array one element at a time:
 *   1. Treat the first element as a sorted part.
 *   2. Take the next element (key) from the unsorted part.
 *   3. Shift all larger elements of the sorted part one place to the right.
 *   4. Insert the key into the gap.
 *   5. Repeat until all elements are processed.
 *
 * Time : O(n)   best case (already sorted)
 *        O(n^2) average and worst case
 * Space: O(1)   (in-place), Stable sort
 */

#include <stdio.h>

#define MAX 100

long comparisons = 0;
long shifts = 0;

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void insertionSort(int arr[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* shift elements greater than key one position to the right */
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                shifts++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;

        printf("Pass %d (key = %-4d): ", i, key);
        displayArray(arr, n);
    }
}

int main() {
    int arr[MAX], n;

    printf("=== Insertion Sort ===\n");
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
    printf("\n");

    insertionSort(arr, n);

    printf("\nSorted array  : ");
    displayArray(arr, n);
    printf("Comparisons = %ld, Shifts = %ld\n", comparisons, shifts);

    return 0;
}