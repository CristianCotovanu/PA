#include <stdio.h>
#include "graph.h"

int main() {
	FILE* fp1 = freopen("testDijkstra.in", "r", stdin);
	int V, type, i, x, y, M, c;
	scanf("%d %d", &V, &type);
	Graph graph1 = initGraph(V, type);
	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &c);
        graph1 = insertEdge(graph1, x, y, c);
	}
    fclose(fp1);

    printGraph(graph1);
	drawGraph(graph1, "Dijkstra.dot");
	Dijkstra(graph1, 0);
    graph1 = freeGraph(graph1);


    FILE* fp2 = freopen("testBellmanFord.in", "r", stdin);
    scanf("%d %d", &V, &type);
    Graph graph2 = initGraph(V, type);
    scanf("%d", &M);
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &c);
        graph2 = insertEdge(graph2, x, y, c);
    }
    fclose(fp2);

//    printGraph(graph2);
    drawGraph(graph2, "BellmanFord.dot");
    BellmanFord(graph2, 0);
    graph2 = freeGraph(graph2);

    return 0;
}
