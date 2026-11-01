/*
 * Binary Search Tree (BST) with all tree traversals - Menu driven program in C
 *
 * Operations : insert, delete, search, find min/max, height, count nodes
 * Traversals : Inorder (L N R), Preorder (N L R), Postorder (L R N),
 *              Level order (breadth first)
 *
 * BST property: for every node, all values in the left subtree are smaller
 * and all values in the right subtree are greater than the node's value.
 * (Duplicate values are not allowed.)
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

/* ---------- Basic functions ---------- */

struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert a value; returns the (possibly new) root */
struct Node *insert(struct Node *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("%d already exists. Duplicates not allowed.\n", value);

    return root;
}

/* Smallest node in a tree */
struct Node *findMin(struct Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

/* Largest node in a tree */
struct Node *findMax(struct Node *root) {
    while (root != NULL && root->right != NULL)
        root = root->right;
    return root;
}

/* Delete a value; returns the new root of the subtree.
 * *found is set to 1 if the value was present. */
struct Node *deleteNode(struct Node *root, int value, int *found) {
    if (root == NULL)
        return NULL;

    if (value < root->data) {
        root->left = deleteNode(root->left, value, found);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value, found);
    } else {
        *found = 1;

        /* Case 1: no child (leaf) */
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        /* Case 2: one child */
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        /* Case 3: two children - replace with inorder successor */
        struct Node *succ = findMin(root->right);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data, found);
    }
    return root;
}

/* Search a value; returns node pointer or NULL */
struct Node *search(struct Node *root, int key) {
    while (root != NULL) {
        if (key == root->data)
            return root;
        root = (key < root->data) ? root->left : root->right;
    }
    return NULL;
}

int height(struct Node *root) {
    if (root == NULL)
        return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

int countNodes(struct Node *root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/* ---------- Traversals ---------- */

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

/* Print all nodes at a given level */
void printLevel(struct Node *root, int level) {
    if (root == NULL)
        return;
    if (level == 1) {
        printf("%d ", root->data);
    } else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void levelOrder(struct Node *root) {
    int h = height(root);
    for (int i = 1; i <= h; i++)
        printLevel(root, i);
}

/* Free the whole tree */
void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

/* ---------- Main ---------- */

int main() {
    struct Node *root = NULL;
    int choice, value, found;

    while (1) {
        printf("\n===== BINARY SEARCH TREE MENU =====\n");
        printf(" 1. Insert\n");
        printf(" 2. Delete\n");
        printf(" 3. Search\n");
        printf(" 4. Inorder traversal\n");
        printf(" 5. Preorder traversal\n");
        printf(" 6. Postorder traversal\n");
        printf(" 7. Level order traversal\n");
        printf(" 8. Show all traversals\n");
        printf(" 9. Find minimum and maximum\n");
        printf("10. Height and node count\n");
        printf(" 0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                if (root == NULL) {
                    printf("Tree is empty!\n");
                    break;
                }
                printf("Enter value to delete: ");
                scanf("%d", &value);
                found = 0;
                root = deleteNode(root, value, &found);
                if (found)
                    printf("%d deleted from the tree.\n", value);
                else
                    printf("%d not found in the tree.\n", value);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value) != NULL)
                    printf("%d is present in the tree.\n", value);
                else
                    printf("%d is not present in the tree.\n", value);
                break;

            case 4:
                if (root == NULL) { printf("Tree is empty!\n"); break; }
                printf("Inorder   (L N R): ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                if (root == NULL) { printf("Tree is empty!\n"); break; }
                printf("Preorder  (N L R): ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                if (root == NULL) { printf("Tree is empty!\n"); break; }
                printf("Postorder (L R N): ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                if (root == NULL) { printf("Tree is empty!\n"); break; }
                printf("Level order      : ");
                levelOrder(root);
                printf("\n");
                break;

            case 8:
                if (root == NULL) { printf("Tree is empty!\n"); break; }
                printf("Inorder   (L N R): ");
                inorder(root);
                printf("\nPreorder  (N L R): ");
                preorder(root);
                printf("\nPostorder (L R N): ");
                postorder(root);
                printf("\nLevel order      : ");
                levelOrder(root);
                printf("\n");
                break;

            case 9:
                if (root == NULL) { printf("Tree is empty!\n"); break; }
                printf("Minimum value: %d\n", findMin(root)->data);
                printf("Maximum value: %d\n", findMax(root)->data);
                break;

            case 10:
                printf("Height of tree: %d\n", height(root));
                printf("Total nodes   : %d\n", countNodes(root));
                break;

            case 0:
                freeTree(root);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    freeTree(root);
    return 0;
}