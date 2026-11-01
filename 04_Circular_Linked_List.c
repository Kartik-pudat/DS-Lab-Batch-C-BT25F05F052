/*
 * Circular Singly Linked List - Menu driven program in C
 * Operations: insert (begin/end/position), delete (begin/end/position),
 *             search, display, count, reverse
 * The last node always points back to the head node.
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
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
    newNode->next = NULL;
    return newNode;
}

/* Return the last node (the one whose next is head) */
struct Node *getLast() {
    struct Node *temp = head;
    while (temp->next != head)
        temp = temp->next;
    return temp;
}

/* Count nodes */
int countNodes() {
    if (head == NULL)
        return 0;
    int count = 0;
    struct Node *temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    return count;
}

/* Insert at beginning */
void insertAtBeginning(int value) {
    struct Node *newNode = createNode(value);
    if (head == NULL) {
        newNode->next = newNode;
        head = newNode;
    } else {
        struct Node *last = getLast();
        newNode->next = head;
        last->next = newNode;
        head = newNode;
    }
    printf("%d inserted at beginning.\n", value);
}

/* Insert at end */
void insertAtEnd(int value) {
    struct Node *newNode = createNode(value);
    if (head == NULL) {
        newNode->next = newNode;
        head = newNode;
    } else {
        struct Node *last = getLast();
        last->next = newNode;
        newNode->next = head;
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
    if (head->next == head) {          /* only one node */
        head = NULL;
    } else {
        struct Node *last = getLast();
        head = head->next;
        last->next = head;
    }
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
    if (head->next == head) {          /* only one node */
        head = NULL;
    } else {
        struct Node *prev = NULL;
        while (temp->next != head) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = head;
    }
    printf("%d deleted from end.\n", temp->data);
    free(temp);
}

/* Delete at a given position (1-based) */
void deleteAtPosition(int pos) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    int n = countNodes();
    if (pos < 1 || pos > n) {
        printf("Invalid position! Valid range: 1 to %d\n", n);
        return;
    }
    if (pos == 1) {
        deleteAtBeginning();
        return;
    }
    struct Node *temp = head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;

    struct Node *del = temp->next;
    temp->next = del->next;
    printf("%d deleted from position %d.\n", del->data, pos);
    free(del);
}

/* Search an element */
void search(int key) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    int pos = 1;
    do {
        if (temp->data == key) {
            printf("%d found at position %d.\n", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != head);
    printf("%d not found in the list.\n", key);
}

/* Display the list */
void display() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    printf("List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(back to head %d)\n", head->data);
}

/* Reverse the list */
void reverseList() {
    if (head == NULL || head->next == head) {
        printf("List reversed.\n");
        return;
    }
    struct Node *prev = getLast();
    struct Node *curr = head;
    struct Node *next;
    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != head);
    head = prev;
    printf("List reversed.\n");
}

/* Free all nodes before exit */
void freeList() {
    if (head == NULL)
        return;
    struct Node *last = getLast();
    last->next = NULL;                 /* break the circle */
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
        printf("\n===== CIRCULAR LINKED LIST MENU =====\n");
        printf(" 1. Insert at beginning\n");
        printf(" 2. Insert at end\n");
        printf(" 3. Insert at position\n");
        printf(" 4. Delete from beginning\n");
        printf(" 5. Delete from end\n");
        printf(" 6. Delete at position\n");
        printf(" 7. Search an element\n");
        printf(" 8. Display list\n");
        printf(" 9. Count nodes\n");
        printf("10. Reverse list\n");
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
                display();
                break;
            case 9:
                printf("Total nodes: %d\n", countNodes());
                break;
            case 10:
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