/*
 * Circular Queue (array implementation) - Menu driven program in C
 * Operations: enqueue, dequeue, peek (front element), display,
 *             isEmpty, isFull, count
 * The rear wraps around to index 0 using modulo (%) so that freed
 * spaces at the front are reused.
 */

#include <stdio.h>

#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

/* Check if queue is empty */
int isEmpty() {
    return (front == -1);
}

/* Check if queue is full */
int isFull() {
    return ((rear + 1) % SIZE == front);
}

/* Number of elements currently in the queue */
int countElements() {
    if (isEmpty())
        return 0;
    return (rear - front + SIZE) % SIZE + 1;
}

/* Insert an element at rear */
void enqueue(int value) {
    if (isFull()) {
        printf("Queue Overflow! Cannot insert %d.\n", value);
        return;
    }
    if (isEmpty()) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % SIZE;
    }
    queue[rear] = value;
    printf("%d inserted into queue.\n", value);
}

/* Remove an element from front */
void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow! Queue is empty.\n");
        return;
    }
    int value = queue[front];
    if (front == rear) {            /* last element removed */
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
    printf("%d deleted from queue.\n", value);
}

/* Show the front element */
void peek() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Front element: %d\n", queue[front]);
}

/* Display all elements from front to rear */
void display() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front -> rear): ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
    printf("Front index = %d, Rear index = %d\n", front, rear);
}

int main() {
    int choice, value;

    while (1) {
        printf("\n===== CIRCULAR QUEUE MENU (size = %d) =====\n", SIZE);
        printf("1. Enqueue (Insert)\n");
        printf("2. Dequeue (Delete)\n");
        printf("3. Peek (Front element)\n");
        printf("4. Display\n");
        printf("5. Count elements\n");
        printf("6. Check if empty\n");
        printf("7. Check if full\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Total elements: %d\n", countElements());
                break;
            case 6:
                printf(isEmpty() ? "Queue is empty.\n" : "Queue is not empty.\n");
                break;
            case 7:
                printf(isFull() ? "Queue is full.\n" : "Queue is not full.\n");
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