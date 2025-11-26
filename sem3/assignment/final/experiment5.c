/*
 * Experiment-5: Demonstrate the efficacy of Prim's and Kruskal's minimal spanning tree algorithms. 
 * Prepare your own input files to prove the correctness of your programs. 
 * There should be output files tracing the different parts of your implementation at different debug levels.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define DEBUG_LEVEL 2

FILE* debugFile;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edges;
    int** adjMatrix;
};

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    
    graph->adjMatrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    
    return graph;
}

// Union-Find for Kruskal's
int find(int parent[], int i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

void Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int compareEdges(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    return e1->weight - e2->weight;
}

// Kruskal's Algorithm
void kruskalMST(struct Graph* graph) {
    fprintf(debugFile, "\n=== KRUSKAL'S ALGORITHM ===\n");
    
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
    
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);
    
    fprintf(debugFile, "Sorted edges by weight:\n");
    for (int j = 0; j < graph->E; j++) {
        fprintf(debugFile, "  Edge %d-%d: weight %d\n", 
                graph->edges[j].src, graph->edges[j].dest, graph->edges[j].weight);
    }
    
    int* parent = (int*)malloc(V * sizeof(int));
    int* rank = (int*)malloc(V * sizeof(int));
    
    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }
    
    fprintf(debugFile, "\nProcessing edges:\n");
    
    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edges[i++];
        
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        
        if (DEBUG_LEVEL >= 2) {
            fprintf(debugFile, "  Checking edge %d-%d (weight: %d)\n", 
                    next_edge.src, next_edge.dest, next_edge.weight);
            fprintf(debugFile, "    Root of %d: %d, Root of %d: %d\n", 
                    next_edge.src, x, next_edge.dest, y);
        }
        
        if (x != y) {
            result[e++] = next_edge;
            Union(parent, rank, x, y);
            fprintf(debugFile, "    -> Added to MST\n");
        } else {
            if (DEBUG_LEVEL >= 1) {
                fprintf(debugFile, "    -> Rejected (creates cycle)\n");
            }
        }
    }
    
    fprintf(debugFile, "\nMST Edges:\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        fprintf(debugFile, "  %d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    fprintf(debugFile, "Total MST Weight: %d\n", totalWeight);
    
    FILE* output = fopen("kruskal_output.txt", "w");
    fprintf(output, "Kruskal's MST Results\n");
    fprintf(output, "======================\n\n");
    fprintf(output, "Edges in MST:\n");
    fprintf(output, "Source\tDestination\tWeight\n");
    fprintf(output, "---------------------------\n");
    for (i = 0; i < e; i++) {
        fprintf(output, "%d\t%d\t\t%d\n", result[i].src, result[i].dest, result[i].weight);
    }
    fprintf(output, "\nTotal Weight: %d\n", totalWeight);
    fclose(output);
    
    free(parent);
    free(rank);
}

// Prim's Algorithm
void primMST(struct Graph* graph) {
    fprintf(debugFile, "\n=== PRIM'S ALGORITHM ===\n");
    
    int V = graph->V;
    int parent[V];
    int key[V];
    int mstSet[V];
    
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    fprintf(debugFile, "Initialization:\n");
    fprintf(debugFile, "  Starting vertex: 0\n");
    
    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        int min = INT_MAX;
        
        for (int v = 0; v < V; v++) {
            if (mstSet[v] == 0 && key[v] < min) {
                min = key[v];
                u = v;
            }
        }
        
        if (u == -1) break;
        
        mstSet[u] = 1;
        
        if (DEBUG_LEVEL >= 2) {
            fprintf(debugFile, "\nIteration %d: Selected vertex %d\n", count + 1, u);
        }
        
        for (int v = 0; v < V; v++) {
            if (graph->adjMatrix[u][v] != 0 && mstSet[v] == 0 && 
                graph->adjMatrix[u][v] < key[v]) {
                key[v] = graph->adjMatrix[u][v];
                parent[v] = u;
                
                if (DEBUG_LEVEL >= 2) {
                    fprintf(debugFile, "  Updated key[%d] = %d, parent[%d] = %d\n", 
                            v, key[v], v, u);
                }
            }
        }
    }
    
    fprintf(debugFile, "\nMST Edges:\n");
    int totalWeight = 0;
    for (int i = 1; i < V; i++) {
        fprintf(debugFile, "  %d - %d : %d\n", parent[i], i, graph->adjMatrix[i][parent[i]]);
        totalWeight += graph->adjMatrix[i][parent[i]];
    }
    fprintf(debugFile, "Total MST Weight: %d\n", totalWeight);
    
    FILE* output = fopen("prim_output.txt", "w");
    fprintf(output, "Prim's MST Results\n");
    fprintf(output, "==================\n\n");
    fprintf(output, "Edges in MST:\n");
    fprintf(output, "Source\tDestination\tWeight\n");
    fprintf(output, "---------------------------\n");
    for (int i = 1; i < V; i++) {
        fprintf(output, "%d\t%d\t\t%d\n", parent[i], i, graph->adjMatrix[i][parent[i]]);
    }
    fprintf(output, "\nTotal Weight: %d\n", totalWeight);
    fclose(output);
}

int main() {
    debugFile = fopen("mst_debug.txt", "w");
    if (debugFile == NULL) {
        printf("Error creating debug file\n");
        return 1;
    }
    
    fprintf(debugFile, "=== MST ALGORITHMS DEBUG TRACE ===\n");
    fprintf(debugFile, "Debug Level: %d\n", DEBUG_LEVEL);
    
    FILE* input = fopen("graph_input.txt", "r");
    if (input == NULL) {
        printf("Creating graph_input.txt...\n");
        input = fopen("graph_input.txt", "w");
        fprintf(input, "5 7\n"); // 5 vertices, 7 edges
        fprintf(input, "0 1 2\n");
        fprintf(input, "0 3 6\n");
        fprintf(input, "1 2 3\n");
        fprintf(input, "1 3 8\n");
        fprintf(input, "1 4 5\n");
        fprintf(input, "2 4 7\n");
        fprintf(input, "3 4 9\n");
        fclose(input);
        input = fopen("graph_input.txt", "r");
    }
    
    int V, E;
    fscanf(input, "%d %d", &V, &E);
    
    struct Graph* graph = createGraph(V, E);
    
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        fscanf(input, "%d %d %d", &src, &dest, &weight);
        graph->edges[i].src = src;
        graph->edges[i].dest = dest;
        graph->edges[i].weight = weight;
        graph->adjMatrix[src][dest] = weight;
        graph->adjMatrix[dest][src] = weight;
    }
    fclose(input);
    
    fprintf(debugFile, "\nGraph:\n");
    fprintf(debugFile, "Vertices: %d, Edges: %d\n", V, E);
    fprintf(debugFile, "Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fprintf(debugFile, "%d ", graph->adjMatrix[i][j]);
        }
        fprintf(debugFile, "\n");
    }
    
    kruskalMST(graph);
    primMST(graph);
    
    fclose(debugFile);
    
    printf("MST algorithms completed!\n");
    printf("Output files generated:\n");
    printf("  - mst_debug.txt (debug trace)\n");
    printf("  - kruskal_output.txt (Kruskal's MST results)\n");
    printf("  - prim_output.txt (Prim's MST results)\n");
    
    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph->edges);
    free(graph);
    
    return 0;
}

