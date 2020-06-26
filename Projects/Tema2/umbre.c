#include <stdio.h>
#include "graph.h"
#include "stack.h"
#include "heap.c"

void addSubstanceCode(int* code, int substNr) {
    *code |= (1 << (substNr - 1));
}

Graph ReadGraphShadows(int** substCodes) {
    FILE* inpFile = fopen("umbre.in", "r");
    int verticesNr, edgesNr, u, v, cost, substances;
    fscanf(inpFile, "%d %d %d", &verticesNr, &edgesNr, &substances);
    Graph graph = initGraph(verticesNr, edgesNr, 0);
    *substCodes = (int* )calloc(verticesNr, sizeof(int));

    for (int node = 0; node < verticesNr; node++) {
        int substNr;
        fscanf(inpFile, "%d", &substNr);

        for (int subst = 0; subst < substNr; subst++) {
            int substIdx;
            fscanf(inpFile,"%d", &substIdx);
            addSubstanceCode(&((*substCodes)[node]), substIdx);
        }
    }

    for (int edge = 0; edge < edgesNr; edge++) {
        fscanf(inpFile, "%d %d %d", &u, &v, &cost);
        // For 0 indexing
        graph = insertEdge(graph, u - 1, v - 1, cost);
    }
    fclose(inpFile);

    return graph;
}

void WriteShadows(int hours) {
    FILE* outFile = fopen("umbre.out", "w");
    fprintf(outFile, "%d", hours);
    fclose(outFile);
}

int comparator(const void *arg1, const void *arg2) {
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;
    return (val1 - val2);
}

void printSubstances(int* substCodes, int nodesNr) {
    printf("[SUBSTANCES]\n");
    for (int i = 0; i < nodesNr; i++) {
        printf("%d ", substCodes[i]);
    }
    printf("\n");
}

int compareMin(const void* e1, const void* e2) {
    Pair p1 = *(Pair*) e1;
    Pair p2 = *(Pair*) e2;

    return p1.cost - p2.cost;
//    if (p1.cost < p2.cost) {
//        return -1;
//    } else if (p1.cost == p2.cost) {
//        return 0;
//    } else {
//        return 1;
//    }
}

void printCost(int verticesNr, int startNode, int* parent, int* distance) {
    for (int node = 0; node < verticesNr; node++) {
        if (node != startNode) {
            printf("\nMinDist from (%d) to (%d) with cost %d.\n", startNode + 1, node + 1, distance[node]);

            int tmp = node;
            Stack printStack = initStack(tmp);
            while (parent[tmp] != -1) {
//                printf("Tmp:%d p[tmp]:%d\n", tmp, parent[tmp]);
                tmp = parent[tmp];
                printStack = push(printStack, tmp);
            }

            while (!isEmptyStack(printStack)) {
                printf("%d -> ", top(printStack) + 1);
                printStack = pop(printStack);
            }

            printf("END");
            freeStack(printStack);
        }
    }
    printf("\n\n");
}

void printHeap(Heap h) {
    printf("\n[HEAP]\n");
    for (int i = 0; i < h->size; i++) {
        printf("Nod:%d dist:%d\n", h->vector[i].v, h->vector[i].cost);
    }
}

void printArray(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
//
//void Dijkstra(Graph g, int start) {
//    int* distance = (int* )calloc(g->V, sizeof(int));
//    int* parent = (int* )calloc(g->V, sizeof(int));
//    Heap minHeap = initHeap(compareMin);
//
//
//    for (int node = 0; node < g->V; node++) {
//        if (start != node && isArc(g, start, node)) {
//            distance[node] = getCost(g, start, node);
//            parent[node] = start;
//
//            Type startNeighbour;
//            startNeighbour.v = node;
//            startNeighbour.cost = getCost(g, start, node);
//            minHeap = insertHeap(minHeap, startNeighbour);
//        } else {
//            distance[node] = INFINITY;
//            parent[node] = -1;
//        }
//    }
//
//    parent[start] = -1;
//    distance[start] = 0;
//    g->visited[start] = 1;
//
//    while (minHeap->size != 0) {
//        Type node = extractMax(minHeap);
////        printf("Nod extras:%d cost:%d dist:%d\n", node.v, node.cost, distance[node.v]);
//        g->visited[node.v] = 1;
//        for (List neighbours = g->adjLists[node.v]; neighbours != NULL; neighbours = neighbours->next) {
//            if (distance[neighbours->data.v]
//                > distance[node.v] + getCost(g, node.v, neighbours->data.v)) {
//
//                distance[neighbours->data.v] = distance[node.v] + getCost(g, node.v, neighbours->data.v);
//                parent[neighbours->data.v] = node.v;
//                minHeap = insertHeap(minHeap, neighbours->data);
//            }
//        }
//    }
//
//    printCost(g->V, start, parent, distance);
//    freeHeap(minHeap);
//    free(distance);
//    free(parent);
//}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void printAllPathsUtil(int **dp, Graph graph, int u, int d, int *visited,
                       int *path, int *path_index, int size, int* substancesCodes) {
    // Mark the current node and store it in path[]
    visited[u] = 1;
    path[*path_index] = u;
    (*path_index)++;
    int j = 0;
    for (int i = 0; i < *path_index; i++) {
        j |= substancesCodes[path[i]];
    }
    int current_d = 0;
    if (*path_index > 1) {
        current_d = getCost(graph, path[0], path[1]);
    }
    if (current_d == INFINITY) {
        current_d = 0;
    }
    for (int i = 2; i < *path_index; i++) {
        current_d += getCost(graph, path[i - 1], path[i]);
    }
    // printf("%d   ---   %d\n", current_d, j);
    if (current_d < dp[u][j]) {
        dp[u][j] = current_d;
    }

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) {
        for (int i = 0; i < *path_index; i++) {
            // printf("%d ", path[i] + 1);
        }
        // printf("\n");

    } else  // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        // list<int>::iterator i;

        List aux = graph->adjLists[u];
        while (aux) {
            int cost = aux->data.v;
            if (aux->data.v < graph->V && j < size) {
                if (!visited[aux->data.v] &&
                    dp[aux->data.v][j] > dp[u][j] + getCost(graph, u, aux->data.v)) {
                    printAllPathsUtil(dp, graph, aux->data.v, d, visited, path,
                                      path_index, size);
                }
            }
            aux = aux->next;
        }
    }

    // Remove current vertex from path[] and mark it as unvisited
    (*path_index)--;
    visited[u] = 0;
}

void printAllPaths(Graph graph, int start, int dest, int size, int* substancesCodes) {
    // Mark all the vertices as not visited
    int *visited = calloc(graph->V, sizeof(int));

    int **dp = calloc(graph->V, sizeof(int));
    for (int i = 0; i < graph->V; i++) {
        dp[i] = calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            dp[i][j] = INFINITY;
        }
    }

    // Create an array to store paths
    int *path = calloc(graph->V, sizeof(int));
    int path_index = 0;  // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < graph->V; i++) {
        visited[i] = 0;
    }

    // Call the recursive helper function to print all paths
    printAllPathsUtil(dp, graph, start, dest, visited, path, &path_index, size, substancesCodes);
    int min_dist = INFINITY;
    for (int j1 = 0; j1 < size; j1++) {
        for (int j2 = 0; j2 < size; j2++) {
            if ((j1 | j2) == size - 1) {
                int current_max = dp[graph->V - 1][j1];
                if (current_max < dp[graph->V - 1][j2]) {
                    current_max = dp[graph->V - 1][j2];
                }
                if (current_max < min_dist) {
                    min_dist = current_max;
                }
            }
        }
    }
    printf("%d\n", min_dist);
}



int main() {
    int* substCodes;
    Graph graph = ReadGraphShadows(&substCodes);

//    printGraph(graph);
//    printSubstances(substCodes, graph->V);
//    Dijkstra(graph, 0);
    printAllPaths(graph, 0, )

    return 0;
}