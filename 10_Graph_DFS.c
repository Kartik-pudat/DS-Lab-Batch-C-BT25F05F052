/*
 * Graph implementation (adjacency matrix) and Depth First Search (DFS)
 * Menu driven program in C
 *
 * Graph     : vertices are numbered 0 to n-1; can be directed or undirected
 * DFS       : goes as deep as possible along each branch before backtracking
 *             - Recursive version (uses the function call stack)
 *             - Iterative version (uses an explicit stack)
 *
 * Time  : O(V^2) with adjacency matrix
 * Space : O(V) for the visited array and the stack
 */

#include <stdio.h>
#include <string.h>

#define MAX 20

int adj[MAX][MAX];      /* adjacency matrix */
int visited[MAX];
int n = 0;              /* number of vertices */
int directed = 0;       /* 1 = directed graph, 0 = undirected */

/* ---------- Graph functions ---------- */

void createGraph() {
    do {
        printf("Enter number of vertices (1 to %d): ", MAX);
        if (scanf("%d", &n) != 1) {
            printf("Invalid input!\n");
            n = 0;
            return;
        }
    } while (n < 1 || n > MAX);

    printf("Type of graph (1 = Directed, 0 = Undirected): ");
    scanf("%d", &directed);
    directed = (directed == 1);

    memset(adj, 0, sizeof(adj));
    printf("Graph with %d vertices (%d to %d) created.\n", n, 0, n - 1);
}

void addEdge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        printf("Invalid vertices! Use values from 0 to %d.\n", n - 1);
        return;
    }
    if (u == v) {
        printf("Self loops are not allowed.\n");
        return;
    }
    if (adj[u][v]) {
        printf("Edge %d -> %d already exists.\n", u, v);
        return;
    }
    adj[u][v] = 1;
    if (!directed)
        adj[v][u] = 1;
    printf("Edge %d %s %d added.\n", u, directed ? "->" : "--", v);
}

void displayMatrix() {
    printf("\nAdjacency Matrix:\n    ");
    for (int i = 0; i < n; i++)
        printf("%3d", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%3d ", i);
        for (int j = 0; j < n; j++)
            printf("%3d", adj[i][j]);
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        printf("%d : ", i);
        for (int j = 0; j < n; j++)
            if (adj[i][j])
                printf("%d ", j);
        printf("\n");
    }
}

void resetVisited() {
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;
}

/* ---------- DFS ---------- */

/* Recursive DFS */
void dfsRecursive(int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++)
        if (adj[v][i] && !visited[i])
            dfsRecursive(i);
}

/* Iterative DFS using an explicit stack */
void dfsIterative(int start) {
    int stack[MAX * MAX];
    int top = -1;

    stack[++top] = start;

    while (top != -1) {
        int v = stack[top--];

        if (visited[v])
            continue;

        visited[v] = 1;
        printf("%d ", v);

        /* push neighbours in reverse so the smallest is visited first */
        for (int i = n - 1; i >= 0; i--)
            if (adj[v][i] && !visited[i])
                stack[++top] = i;
    }
}

/* DFS over the whole graph (also covers disconnected components) */
void dfsWholeGraph() {
    int components = 0;
    resetVisited();
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;
            printf("Component %d: ", components);
            dfsRecursive(i);
            printf("\n");
        }
    }
    printf("Number of connected components (reachable groups): %d\n", components);
}

/* ---------- Main ---------- */

int main() {
    int choice, u, v;

    createGraph();
    if (n == 0)
        return 1;

    while (1) {
        printf("\n===== GRAPH & DFS MENU =====\n");
        printf("1. Add edge\n");
        printf("2. Display graph\n");
        printf("3. DFS traversal (recursive)\n");
        printf("4. DFS traversal (iterative using stack)\n");
        printf("5. DFS of whole graph (all components)\n");
        printf("6. Create a new graph\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter edge (u v): ");
                scanf("%d %d", &u, &v);
                addEdge(u, v);
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                printf("Enter starting vertex: ");
                scanf("%d", &u);
                if (u < 0 || u >= n) {
                    printf("Invalid vertex!\n");
                    break;
                }
                resetVisited();
                printf("DFS (recursive) from %d: ", u);
                dfsRecursive(u);
                printf("\n");
                break;

            case 4:
                printf("Enter starting vertex: ");
                scanf("%d", &u);
                if (u < 0 || u >= n) {
                    printf("Invalid vertex!\n");
                    break;
                }
                resetVisited();
                printf("DFS (iterative) from %d: ", u);
                dfsIterative(u);
                printf("\n");
                break;

            case 5:
                dfsWholeGraph();
                break;

            case 6:
                createGraph();
                if (n == 0)
                    return 1;
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