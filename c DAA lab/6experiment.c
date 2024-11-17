#include <stdio.h>
#include <limits.h>
#include <time.h>

#define V 5 // Number of vertices

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra's algorithm for shortest path in a graph
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // The output array dist[i] will hold the shortest distance from src to i
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in the shortest path tree
    
    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance from the source vertex to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);
        
        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update the distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distances
    printf("\nDijkstra's Shortest Path from vertex %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("INF ");
        else
            printf("%d ", dist[i]);
    }
    printf("\n");
}

// Bellman-Ford algorithm for shortest path in a graph
void bellmanFord(int graph[V][V], int src) {
    int dist[V];
    
    // Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                printf("Graph contains negative weight cycle\n");
                return;
            }
        }
    }

    // Print the shortest distances
    printf("\nBellman-Ford Shortest Path from vertex %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("INF ");
        else
            printf("%d ", dist[i]);
    }
    printf("\n");
}

// Function to measure the time taken by an algorithm
void measureTime(void (*algo)(int[V][V], int), int graph[V][V], int src, const char* algoName) {
    clock_t start, end;
    start = clock();
    algo(graph, src);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s took %.10f seconds\n", algoName, time_taken);
}

int main() {
    // Example graph with 5 vertices
    int graph[V][V] = {
        {0, 2, 0, 1, 0},
        {2, 0, 3, 0, 5},
        {0, 3, 0, 1, 2},
        {1, 0, 1, 0, 4},
        {0, 5, 2, 4, 0}
    };

    int src = 0; // Starting vertex (0-indexed)

    // Measure and compare the performance of Dijkstra and Bellman-Ford
    measureTime(dijkstra, graph, src, "Dijkstra");
    measureTime(bellmanFord, graph, src, "Bellman-Ford");

    return 0;
}
