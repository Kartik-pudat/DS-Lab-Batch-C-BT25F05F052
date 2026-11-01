/*
 * Bubble Sort and Merge Sort - Menu driven program in C
 *
 * Bubble Sort : repeatedly compares adjacent elements and swaps them if
 *               they are in the wrong order (optimized with a swapped flag).
 *               Time: O(n^2) worst/average, O(n) best.   Space: O(1)
 *
 * Merge Sort  : divide and conquer - split the array into two halves, sort
 *               each half recursively, then merge the two sorted halves.
 *               Time: O(n log n) in all cases.           Space: O(n)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

long comparisons = 0;   /* number of comparisons made */
long operations  = 0;   /* swaps (bubble) or element copies (merge) */

/* ---------- Helper functions ---------- */

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

/* ---------- Bubble Sort ---------- */

void bubbleSort(int arr[], int n) {
    int i, j, temp, swapped;

    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                operations++;
                swapped = 1;
            }
        }
        printf("Pass %d: ", i + 1);
        displayArray(arr, n);

        if (swapped == 0)       /* already sorted, stop early */
            break;
    }
}

/* ---------- Merge Sort ---------- */

/* Merge arr[left..mid] and arr[mid+1..right] */
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int i, j, k;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
        operations++;
    }

    while (i < n1) {            /* copy remaining elements of L */
        arr[k++] = L[i++];
        operations++;
    }
    while (j < n2) {            /* copy remaining elements of R */
        arr[k++] = R[j++];
        operations++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);

        printf("Merged [%d..%d]: ", left, right);
        for (int i = left; i <= right; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
}

/* ---------- Main ---------- */

void readArray(int arr[], int *n) {
    do {
        printf("Enter number of elements (1 to %d): ", MAX);
        scanf("%d", n);
    } while (*n < 1 || *n > MAX);

    printf("Enter %d elements: ", *n);
    for (int i = 0; i < *n; i++)
        scanf("%d", &arr[i]);
}

int main() {
    int original[MAX], work[MAX];
    int n, choice;

    readArray(original, &n);

    while (1) {
        printf("\n===== SORTING MENU =====\n");
        printf("1. Bubble Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Compare both (comparisons count)\n");
        printf("4. Enter a new array\n");
        printf("5. Display original array\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                copyArray(original, work, n);
                comparisons = 0;
                operations = 0;
                printf("\nBefore sorting: ");
                displayArray(work, n);
                bubbleSort(work, n);
                printf("After Bubble Sort: ");
                displayArray(work, n);
                printf("Comparisons = %ld, Swaps = %ld\n", comparisons, operations);
                break;

            case 2:
                copyArray(original, work, n);
                comparisons = 0;
                operations = 0;
                printf("\nBefore sorting: ");
                displayArray(work, n);
                mergeSort(work, 0, n - 1);
                printf("After Merge Sort: ");
                displayArray(work, n);
                printf("Comparisons = %ld, Element copies = %ld\n", comparisons, operations);
                break;

            case 3: {
                long bubbleComp, mergeComp;

                copyArray(original, work, n);
                comparisons = 0;
                operations = 0;
                printf("\n--- Bubble Sort ---\n");
                bubbleSort(work, n);
                bubbleComp = comparisons;

                copyArray(original, work, n);
                comparisons = 0;
                operations = 0;
                printf("\n--- Merge Sort ---\n");
                mergeSort(work, 0, n - 1);
                mergeComp = comparisons;

                printf("\nSorted array: ");
                displayArray(work, n);
                printf("Bubble Sort comparisons: %ld\n", bubbleComp);
                printf("Merge Sort comparisons : %ld\n", mergeComp);
                break;
            }

            case 4:
                readArray(original, &n);
                break;

            case 5:
                printf("Original array: ");
                displayArray(original, n);
                break;

            case 0:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}