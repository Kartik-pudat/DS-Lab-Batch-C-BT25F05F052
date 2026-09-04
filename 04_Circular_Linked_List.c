#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *last = NULL;

// Insert at beginning
void insertBeginning(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;

    if (last == NULL) {
        last = newNode;
        newNode->next = last;
    } else {
        newNode->next = last->next;
        last->next = newNode;
    }
}

// Insert at end
void insertEnd(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;

    if (last == NULL) {
        last = newNode;
        newNode->next = last;
    } else {
        newNode->next = last->next;
        last->next = newNode;
        last = newNode;
    }
}

// Delete from beginning
void deleteBeginning() {
    if (last == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = last->next;

    if (last == temp) {
        last = NULL;
    } else {
        last->next = temp->next;
    }

    free(temp);
}

// Display
void display() {
    if (last == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = last->next;

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != last->next);

    printf("(back to first node)\n");
}

int main() {
    insertEnd(10);
    insertEnd(20);
    insertEnd(30);

    printf("Circular Linked List:\n");
    display();

    insertBeginning(5);

    printf("After inserting 5 at beginning:\n");
    display();

    deleteBeginning();

    printf("After deleting first node:\n");
    display();

    return 0;
}