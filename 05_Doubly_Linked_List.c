/*
 * Doubly Linked List - Menu driven program in C
 * Operations: insert (begin/end/position), delete (begin/end/position),
 *             search, display (forward/backward), count, reverse
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

/* Create a new node */
struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/* Count nodes */
int countNodes() {
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

/* Insert at beginning */
void insertAtBeginning(int value) {
    struct Node *newNode = createNode(value);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
    printf("%d inserted at beginning.\n", value);
}

/* Insert at end */
void insertAtEnd(int value) {
    struct Node *newNode = createNode(value);
    if (head == NULL) {
        head = newNode;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("%d inserted at end.\n", value);
}

/* Insert at a given position (1-based) */
void insertAtPosition(int value, int pos) {
    int n = countNodes();
    if (pos < 1 || pos > n + 1) {
        printf("Invalid position! Valid range: 1 to %d\n", n + 1);
        return;
    }
    if (pos == 1) {
        insertAtBeginning(value);
        return;
    }
    struct Node *temp = head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;

    struct Node *newNode = createNode(value);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = newNode;
    temp->next = newNode;
    printf("%d inserted at position %d.\n", value, pos);
}

/* Delete from beginning */
void deleteAtBeginning() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    printf("%d deleted from beginning.\n", temp->data);
    free(temp);
}

/* Delete from end */
void deleteAtEnd() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev != NULL)
        temp->prev->next = NULL;
    else
        head = NULL;   /* only one node */

    printf("%d deleted from end.\n", temp->data);
    free(temp);
}

/* Delete at a given position (1-based) */
void deleteAtPosition(int pos) {
    int n = countNodes();
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    if (pos < 1 || pos > n) {
        printf("Invalid position! Valid range: 1 to %d\n", n);
        return;
    }
    if (pos == 1) {
        deleteAtBeginning();
        return;
    }
    struct Node *temp = head;
    for (int i = 1; i < pos; i++)
        temp = temp->next;

    temp->prev->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    printf("%d deleted from position %d.\n", temp->data, pos);
    free(temp);
}

/* Search an element */
void search(int key) {
    struct Node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("%d found at position %d.\n", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("%d not found in the list.\n", key);
}

/* Display forward */
void displayForward() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    printf("Forward : NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* Display backward */
void displayBackward() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    printf("Backward: NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

/* Reverse the list */
void reverseList() {
    struct Node *current = head;
    struct Node *temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL)
        head = temp->prev;
    printf("List reversed.\n");
}

/* Free all nodes before exit */
void freeList() {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice, value, pos;

    while (1) {
        printf("\n===== DOUBLY LINKED LIST MENU =====\n");
        printf(" 1. Insert at beginning\n");
        printf(" 2. Insert at end\n");
        printf(" 3. Insert at position\n");
        printf(" 4. Delete from beginning\n");
        printf(" 5. Delete from end\n");
        printf(" 6. Delete at position\n");
        printf(" 7. Search an element\n");
        printf(" 8. Display forward\n");
        printf(" 9. Display backward\n");
        printf("10. Count nodes\n");
        printf("11. Reverse list\n");
        printf(" 0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtBeginning(value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;
            case 3:
                printf("Enter value and position: ");
                scanf("%d %d", &value, &pos);
                insertAtPosition(value, pos);
                break;
            case 4:
                deleteAtBeginning();
                break;
            case 5:
                deleteAtEnd();
                break;
            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deleteAtPosition(pos);
                break;
            case 7:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(value);
                break;
            case 8:
                displayForward();
                break;
            case 9:
                displayBackward();
                break;
            case 10:
                printf("Total nodes: %d\n", countNodes());
                break;
            case 11:
                reverseList();
                break;
            case 0:
                freeList();
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    freeList();
    return 0;
}