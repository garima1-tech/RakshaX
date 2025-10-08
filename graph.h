// graph.h
#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int vertices;
    int **adjMatrix;
} Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* g, int src, int dest, int weight);
void BFS(Graph* g, int start);
void dijkstra(Graph* g, int start);
void freeGraph(Graph* g);

#endif
