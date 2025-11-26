/*
 * Experiment-6: Demonstrate the efficacy of Dijkstra's minimum path algorithm. 
 * Prepare your own input files to prove the correctness of your programs. 
 * There should be output files tracing the different parts of your implementation at different debug levels.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define DEBUG_LEVEL 2

FILE* debugFile;

int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    
    return min_index;
}

void printPath(int parent[], int j, FILE* output) {
    if (parent[j] == -1) {
        fprintf(output, "%d", j);
        return;
    }
    printPath(parent, parent[j], output);
    fprintf(output, " -> %d", j);
}

void dijkstra(int** graph, int src, int V) {
    fprintf(debugFile, "\n=== DIJKSTRA'S ALGORITHM ===\n");
    fprintf(debugFile, "Source vertex: %d\n", src);
    fprintf(debugFile, "Number of vertices: %d\n", V);
    
    int dist[V];
    int sptSet[V];
    int parent[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }
    
    dist[src] = 0;
    parent[src] = -1;
    
    fprintf(debugFile, "\nInitialization:\n");
    fprintf(debugFile, "  Distance from source:\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            fprintf(debugFile, "    dist[%d] = INF\n", i);
        } else {
            fprintf(debugFile, "    dist[%d] = %d\n", i, dist[i]);
        }
    }
    
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        
        sptSet[u] = 1;
        
        fprintf(debugFile, "\nIteration %d: Selected vertex %d\n", count + 1, u);
        fprintf(debugFile, "  Processing neighbors of vertex %d:\n", u);
        
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                
                int oldDist = dist[v];
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
                
                if (DEBUG_LEVEL >= 2) {
                    if (oldDist == INT_MAX) {
                        fprintf(debugFile, "    Vertex %d: dist = INF -> %d (via %d)\n", 
                                v, dist[v], u);
                    } else {
                        fprintf(debugFile, "    Vertex %d: dist = %d -> %d (via %d)\n", 
                                v, oldDist, dist[v], u);
                    }
                }
            } else if (DEBUG_LEVEL >= 2 && graph[u][v] != 0 && !sptSet[v]) {
                fprintf(debugFile, "    Vertex %d: No update (current: ", v);
                if (dist[v] == INT_MAX) {
                    fprintf(debugFile, "INF");
                } else {
                    fprintf(debugFile, "%d", dist[v]);
                }
                fprintf(debugFile, ", new would be: ");
                if (dist[u] == INT_MAX) {
                    fprintf(debugFile, "INF");
                } else {
                    fprintf(debugFile, "%d", dist[u] + graph[u][v]);
                }
                fprintf(debugFile, ")\n");
            }
        }
        
        if (DEBUG_LEVEL >= 1) {
            fprintf(debugFile, "  Current distances: ");
            for (int i = 0; i < V; i++) {
                if (dist[i] == INT_MAX) {
                    fprintf(debugFile, "INF ");
                } else {
                    fprintf(debugFile, "%d ", dist[i]);
                }
            }
            fprintf(debugFile, "\n");
        }
    }
    
    fprintf(debugFile, "\nFinal Results:\n");
    FILE* output = fopen("dijkstra_output.txt", "w");
    fprintf(output, "Dijkstra's Shortest Path Algorithm Results\n");
    fprintf(output, "==========================================\n\n");
    fprintf(output, "Source vertex: %d\n\n", src);
    fprintf(output, "Vertex\tDistance\tPath\n");
    fprintf(output, "----------------------------------------\n");
    
    for (int i = 0; i < V; i++) {
        fprintf(output, "%d\t", i);
        if (dist[i] == INT_MAX) {
            fprintf(output, "INF\t\tNo path");
        } else {
            fprintf(output, "%d\t\t", dist[i]);
            printPath(parent, i, output);
        }
        fprintf(output, "\n");
        
        if (DEBUG_LEVEL >= 1) {
            fprintf(debugFile, "  Vertex %d: Distance = ", i);
            if (dist[i] == INT_MAX) {
                fprintf(debugFile, "INF");
            } else {
                fprintf(debugFile, "%d", dist[i]);
            }
            fprintf(debugFile, ", Path: ");
            if (dist[i] != INT_MAX) {
                printPath(parent, i, debugFile);
            } else {
                fprintf(debugFile, "No path");
            }
            fprintf(debugFile, "\n");
        }
    }
    
    fclose(output);
}

int main() {
    debugFile = fopen("dijkstra_debug.txt", "w");
    if (debugFile == NULL) {
        printf("Error creating debug file\n");
        return 1;
    }
    
    fprintf(debugFile, "=== DIJKSTRA'S ALGORITHM DEBUG TRACE ===\n");
    fprintf(debugFile, "Debug Level: %d\n", DEBUG_LEVEL);
    
    FILE* input = fopen("graph_input_dijkstra.txt", "r");
    if (input == NULL) {
        printf("Creating graph_input_dijkstra.txt...\n");
        input = fopen("graph_input_dijkstra.txt", "w");
        fprintf(input, "6 9\n"); // 6 vertices, 9 edges
        fprintf(input, "0 1 4\n");
        fprintf(input, "0 2 2\n");
        fprintf(input, "1 2 1\n");
        fprintf(input, "1 3 5\n");
        fprintf(input, "2 3 8\n");
        fprintf(input, "2 4 10\n");
        fprintf(input, "3 4 2\n");
        fprintf(input, "3 5 6\n");
        fprintf(input, "4 5 3\n");
        fclose(input);
        input = fopen("graph_input_dijkstra.txt", "r");
    }
    
    int V, E;
    fscanf(input, "%d %d", &V, &E);
    
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    
    fprintf(debugFile, "\nGraph:\n");
    fprintf(debugFile, "Vertices: %d, Edges: %d\n", V, E);
    
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        fscanf(input, "%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight; // Undirected graph
        fprintf(debugFile, "  Edge: %d - %d (weight: %d)\n", src, dest, weight);
    }
    fclose(input);
    
    fprintf(debugFile, "\nAdjacency Matrix:\n");
    fprintf(debugFile, "   ");
    for (int i = 0; i < V; i++) {
        fprintf(debugFile, "%3d ", i);
    }
    fprintf(debugFile, "\n");
    for (int i = 0; i < V; i++) {
        fprintf(debugFile, "%2d ", i);
        for (int j = 0; j < V; j++) {
            fprintf(debugFile, "%3d ", graph[i][j]);
        }
        fprintf(debugFile, "\n");
    }
    
    int source = 0;
    dijkstra(graph, source, V);
    
    fclose(debugFile);
    
    printf("Dijkstra's algorithm completed!\n");
    printf("Output files generated:\n");
    printf("  - dijkstra_debug.txt (debug trace)\n");
    printf("  - dijkstra_output.txt (shortest path results)\n");
    
    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    
    return 0;
}

