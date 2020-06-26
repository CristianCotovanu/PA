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
    drawGraph(graph, "graph1.dot");

	articulationPointsTarjan(graph);

    // freopen("test1.in", "r", stdin);
    // scanf("%d %d", &V, &type);
    // graph = initGraph(V, type);
    // scanf("%d", &M);
    // for (i = 0; i < M; i++) {
    //     scanf("%d %d", &x, &y);
    //     graph = insertEdge(graph, x, y);
    // }
    // drawGraph(graph, "graph2.dot");

    bridgesTarjan(graph);


    fclose(stdin);
	return 0;
}