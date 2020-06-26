#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"

int main() {
	freopen("test1.in", "r", stdin);
	int V, type, i, x, y, M;
	scanf("%d %d", &V, &type);
	Graph graph = initGraph(V, type);
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d", &x, &y);
		graph = insertEdge(graph, x, y);
	}
	bfs(graph, 0);
	dfs(graph, 0);
    dfs(graph, 3);
    recursiveDFS(graph, 0);
    drawGraph(graph, "graph1.dot");

    fclose(stdin);

    freopen("test1.in", "r", stdin);
    scanf("%d %d", &V, &type);
    graph = initGraph(V, 1);
    scanf("%d", &M);
    for (int j = 0; j < M; j++) {
        scanf("%d %d", &x, &y);
        graph = insertEdge(graph, x, y);
    }

    // topologicalSortDfs(graph);
    topoSortKhanAlgorithm(graph);

    fclose(stdin);
	return 0;
}