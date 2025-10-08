// graph.c
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Create a graph with given number of vertices
Graph* createGraph(int vertices) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertices = vertices;

    g->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        g->adjMatrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    return g;
}

// Add an edge (undirected)
void addEdge(Graph* g, int src, int dest, int weight) {
    if (src < g->vertices && dest < g->vertices) {
        g->adjMatrix[src][dest] = weight;
        g->adjMatrix[dest][src] = weight;
    }
}

// Simple BFS traversal
void BFS(Graph* g, int start) {
    int *visited = (int*)calloc(g->vertices, sizeof(int));
    int queue[1000], front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS Traversal: ");
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);
        for (int i = 0; i < g->vertices; i++) {
            if (g->adjMatrix[v][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
    free(visited);
}

// Dijkstra's Algorithm (shortest path)
void dijkstra(Graph* g, int start) {
    int n = g->vertices;
    int dist[100], visited[100];
    for (int i = 0; i < n; i++) {
        dist[i] = 9999;
        visited[i] = 0;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = 9999, u = -1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && dist[v] <= min)
                min = dist[v], u = v;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && g->adjMatrix[u][v] &&
                dist[u] + g->adjMatrix[u][v] < dist[v])
                dist[v] = dist[u] + g->adjMatrix[u][v];
        }
    }

    printf("\nDijkstra (from %d):\n", start);
    for (int i = 0; i < n; i++)
        printf("To %d: %d\n", i, dist[i]);
}

// Free all memory
void freeGraph(Graph* g) {
    for (int i = 0; i < g->vertices; i++)
        free(g->adjMatrix[i]);
    free(g->adjMatrix);
    free(g);
}
