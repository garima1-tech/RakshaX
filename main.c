#include <stdio.h>
#include <stdlib.h>       // for calloc, free
#include "graph.h"
#include "priority_queue.h"
#include "scheduler.h"
#include "disaster.h"
#include "utils.h"
#include "sms.h"
#include "sensor.h"
#include "logger.h"

int main() {
    printf("=== Crisis to Care: RakshaX ===\n");

    DisasterZone zones[10];
    int zoneCount = loadDisasterZones("datasets/zones.txt", zones, 10);

    initLogger("datasets/history.log");

    FILE* outFile = fopen("datasets/output.txt", "w");
    if (!outFile) {
        printf("Cannot open output file\n");
        return 1;
    }

    MaxHeap* pq = createMaxHeap(zoneCount);
    for (int i = 0; i < zoneCount; i++)
        insertMaxHeap(pq, zones[i]);

    fprintf(outFile, "=== Dispatch Log ===\n");
    while (!isEmpty(pq)) {
        DisasterZone z = extractMax(pq);
        fprintf(outFile, "Dispatching Zone %d (Severity %d, Population %d, LastHelp %d)\n",
                z.id, z.severity, z.population, z.lastHelp);
        logZoneDispatch(z);
        sendSMS("9999999999", "Resources dispatched!");
    }

    Graph* g = createGraph(6);
    addEdge(g, 0, 1, 2);
    addEdge(g, 1, 2, 3);

    fprintf(outFile, "\nBFS Traversal: ");
    int *visited = (int*)calloc(g->vertices, sizeof(int));
    int queue[1000], front = 0, rear = 0;
    visited[0] = 1;
    queue[rear++] = 0;
    while (front < rear) {
        int v = queue[front++];
        fprintf(outFile, "%d ", v);
        for (int i = 0; i < g->vertices; i++) {
            if (g->adjMatrix[v][i] != 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    free(visited);   // now free is recognized
    fprintf(outFile, "\n");

    // Dijkstra
    int n = g->vertices;
    int dist[100], vis[100];
    for (int i = 0; i < n; i++) { dist[i] = 9999; vis[i] = 0; }
    dist[0] = 0;
    for (int count = 0; count < n-1; count++) {
        int min = 9999, u = -1;
        for (int v = 0; v < n; v++)
            if (!vis[v] && dist[v] <= min) min = dist[v], u = v;
        if(u == -1) break;
        vis[u] = 1;
        for (int v = 0; v < n; v++) {
            if (!vis[v] && g->adjMatrix[u][v] &&
                dist[u] + g->adjMatrix[u][v] < dist[v])
                dist[v] = dist[u] + g->adjMatrix[u][v];
        }
    }
    fprintf(outFile, "\nDijkstra (from 0):\n");
    for (int i = 0; i < n; i++)
        fprintf(outFile, "To %d: %d\n", i, dist[i]);

    fclose(outFile);
    closeLogger();
    freeMaxHeap(pq);
    freeGraph(g);

    printf("Output written to datasets/output.txt\n");
    return 0;
}
