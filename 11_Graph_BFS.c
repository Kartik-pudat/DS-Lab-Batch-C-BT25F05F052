/*
 * Graph implementation (adjacency matrix) and Breadth First Search (BFS)
 * Menu driven program in C
 *
 * Graph : vertices are numbered 0 to n-1; can be directed or undirected
 * BFS   : visits all vertices at distance 1 from the start, then distance 2,
 *         and so on (level by level) using a QUEUE.
 *
 * Algorithm:
 *   1. Mark the start vertex visited and enqueue it.
 *   2. Dequeue a vertex, print it.
 *   3. Enqueue all its unvisited neighbours (marking them visited).
 *   4. Repeat steps 2-3 until the queue is empty.
 *
 * Time  : O(V^2) with adjacency matrix
 * Space : O(V) for the visited array and the queue
 */

#include <stdio.h>
#include <string.h>

#define MAX 20

int adj[MAX][MAX];      /* adjacency matrix */
int visited[MAX];
int dist[MAX];          /* distance (number of edges) from the start vertex */
int n = 0;              /* number of vertices */
int directed = 0;       /* 1 = directed graph, 0 = undirected */

/* ---------- Queue (array based, used by BFS) ---------- */

int queue[MAX];
int front = 0, rear = -1;

void resetQueue() {
    front = 0;
    rear = -1;
}

int isQueueEmpty() {
    return front > rear;
}

void enqueue(int v) {
    queue[++rear] = v;     /* each vertex is enqueued at most once, so MAX is enough */
}

int dequeue() {
    return queue[front++];
}

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
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
        dist[i] = -1;
    }
}

/* ---------- BFS ---------- */

/* BFS from one start vertex; prints the visiting order */
void bfs(int start) {
    resetQueue();

    visited[start] = 1;
    dist[start] = 0;
    enqueue(start);

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v);

        for (int i = 0; i < n; i++) {
            if (adj[v][i] && !visited[i]) {
                visited[i] = 1;
                dist[i] = dist[v] + 1;
                enqueue(i);
            }
        }
    }
}

/* BFS from a start vertex, then show the level (distance) of every vertex */
void bfsWithLevels(int start) {
    resetVisited();
    printf("BFS from %d: ", start);
    bfs(start);
    printf("\n\nVertex : Distance from %d (number of edges)\n", start);
    for (int i = 0; i < n; i++) {
        if (dist[i] == -1)
            printf("  %d    : not reachable\n", i);
        else
            printf("  %d    : %d\n", i, dist[i]);
    }
}

/* BFS over the whole graph (also covers disconnected components) */
void bfsWholeGraph() {
    int components = 0;
    resetVisited();
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;
            printf("Component %d: ", components);
            bfs(i);
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
        printf("\n===== GRAPH & BFS MENU =====\n");
        printf("1. Add edge\n");
        printf("2. Display graph\n");
        printf("3. BFS traversal from a vertex\n");
        printf("4. BFS with distance (level) of each vertex\n");
        printf("5. BFS of whole graph (all components)\n");
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
                printf("BFS from %d: ", u);
                bfs(u);
                printf("\n");
                break;

            case 4:
                printf("Enter starting vertex: ");
                scanf("%d", &u);
                if (u < 0 || u >= n) {
                    printf("Invalid vertex!\n");
                    break;
                }
                bfsWithLevels(u);
                break;

            case 5:
                bfsWholeGraph();
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