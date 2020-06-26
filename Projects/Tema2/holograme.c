#include <stdio.h>
#include "graph.h"

typedef struct set {
    int ancestor;
    int rank;
} Set;

int FindUnion(Set subsets[], int ancIdx) {
    if (subsets[ancIdx].ancestor != ancIdx) {
        subsets[ancIdx].ancestor = FindUnion(subsets,
                subsets[ancIdx].ancestor);
    }
    return subsets[ancIdx].ancestor;
}


void Union(Set subsets[], int comp1, int comp2) {
    int arb1 = FindUnion(subsets, comp1);
    int arb2 = FindUnion(subsets, comp2);

    if (subsets[arb1].rank == subsets[arb2].rank) {
        subsets[arb2].ancestor = arb1;
        subsets[arb1].rank++;
    } else if (subsets[arb1].rank < subsets[arb2].rank) {
        subsets[arb1].ancestor = arb2;
    } else {
        subsets[arb2].ancestor = arb1;
    }
}

Set* InitSets(int ssNum) {
    Set *subsets = (Set*) calloc(ssNum, sizeof(Set));
    for (int i = 0; i < ssNum; ++i) {
        subsets[i].ancestor = i;
        subsets[i].rank = 0;
    }
    return subsets;
}

Edge* BuildEdgesList(Graph graph) {
    Edge* edges = (Edge* )calloc(graph->E, sizeof(Edge));
    int edgeCnt = 0;

    for (int node = 1; node < graph->V; node++) {
        for (List neighbours = graph->adjLists[node]; neighbours != NULL;
                neighbours = neighbours->next) {
            Edge tmpEdge;
            tmpEdge.cost = 1;
            tmpEdge.src = node;
            tmpEdge.dst = neighbours->data.v;
            edges[edgeCnt++] = tmpEdge;
        }
    }

    return edges;
}

Graph ReadGraphHolograms() {
    FILE* inpFile = fopen("holograme.in", "r");
    int verticesNr, edgesNr, u, v;
    fscanf(inpFile, "%d %d", &verticesNr, &edgesNr);
    Graph graph = initGraph(verticesNr + 1, edgesNr, 1);
    for (int edge = 0; edge < edgesNr; edge++) {
        fscanf(inpFile, "%d %d", &u, &v);
        graph = insertEdge(graph, u, v, 1);
    }
    fclose(inpFile);
    return graph;
}

void WriteHolograms(int edges) {
    FILE* outFile = fopen("holograme.out", "w");
    fprintf(outFile, "%d", edges);
    fclose(outFile);
}

void Free(Edge* edges, Set* sets) {
    free(edges);
    free(sets);
}

int HologramsFind(Graph graph) {
    int mstEdges = 0;
    Edge* edges = BuildEdgesList(graph);
    Set* sets = InitSets(graph->V);

    // Choose edges to create the MST in number of V - 1
    for (int i = 0; i < graph->E && mstEdges < graph->V - 1; i++) {
        Edge next_edge = edges[i];

        int comp1 = FindUnion(sets, next_edge.src);
        int comp2 = FindUnion(sets, next_edge.dst);

        if (comp1 != comp2) {
            Union(sets, comp1, comp2);
            mstEdges++;
        }
    }

    mstEdges = (graph->E - 1 <= mstEdges) ? mstEdges : mstEdges + 1;
    Free(edges, sets);
    return mstEdges;
}

int main() {
    Graph graph = ReadGraphHolograms();
    WriteHolograms(HologramsFind(graph));
    freeGraph(graph);

    return 0;
}
