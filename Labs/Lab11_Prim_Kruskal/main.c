#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"

int main() {
	freopen("testMST.in", "r", stdin);
	int V, type, i, x, y, M, cost;
	scanf("%d %d", &V, &type);
	Graph graph = initGraph(V, type);
	scanf("%d", &M);
	graph->E = M;
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &cost);
		graph = insertEdge(graph, x, y, cost);
	}
	// printGraph(graph);
	// drawGraph(graph, "graph1.dot");
	
	Kruskal(graph);
	int startNode = 1;
	Prim(graph, startNode);

	graph = freeGraph(graph);
	return 0;
}