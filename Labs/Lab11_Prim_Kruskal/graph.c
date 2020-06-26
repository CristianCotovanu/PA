#include <string.h>
#include "graph.h"
#include "heap.c"

Graph initGraph(int V, int type) {
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	g->type = type;
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(V, sizeof(int));
	g->start = malloc(V * sizeof(int));
	g->end = malloc(V * sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost) {
	Pair p;
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);

	if (g->type == 0) {
		Pair p1;
		p.v = u;
		p.cost = cost;
		g->adjLists[v] = addLast(g->adjLists[v], p);
	}
	return g;
}

int isArc(Graph g, int u, int v) {
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v) {
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return INFINITY;
}

void drawGraph(Graph g, char *name) {
	int i, j;
	FILE *stream;
	char *buffer, *aux;
	List tmp;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	if (g->type == 0)
		fprintf(stream, "graph G {\n");
	else
		fprintf(stream, "digraph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->V; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			if (g->type == 0) {
				if (i < tmp->data.v)
					fprintf(stream, "    %d -- %d;\n", i, tmp->data.v);
			}
			else
				fprintf(stream, "    %d -> %d;\n", i, tmp->data.v);
			tmp = tmp->next;
		}
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	aux = (char*) malloc(SIZE*sizeof(char));
	strncpy(aux, name, strlen(name) - 4);
	aux[strlen(name) - 4] = '\0';
	sprintf(buffer, "dot %s | neato -n -Tpng -o %s.png", name, aux);
	system(buffer);
	free(buffer);
	free(aux);
}

void printGraph(Graph g) {
	int i;
	if (g == NULL)
		return;
	if (g->type == 0)
		printf("Graf neorientat cu %d noduri\n", g->V);
	else
		printf("Graf orientat cu %d noduri\n", g->V);
	for (i = 0; i < g->V; i++) {
		printf("%d: ", i);
		List adj = g->adjLists[i];
		while (adj) {
			printf("(%d, %d) -> ", adj->data.v, adj->data.cost);
			adj = adj->next;
		}
		printf("NULL\n");
	}
}

Graph freeGraph(Graph graph) {
	int i;
	if (!graph)
		return graph;
	if (graph->visited)
		free(graph->visited);
	if (graph->start)
		free(graph->start);
	if (graph->end)
		free(graph->end);
	if (graph->adjLists) {
		for (i = 0; i < graph->V; i++)
			graph->adjLists[i] = freeList(graph->adjLists[i]);
		free(graph->adjLists);
	}
	free(graph);
	return NULL;
}

int comparatorEdges(const void* arg1, const void* arg2) {
	int c1 = (*(Edge*)arg1).cost;
	int c2 = (*(Edge*)arg2).cost;

	return c1 - c2;
}

int validEdge(Edge* edges, int u, int v, int edgesNr) {
	for (int i = 0; i < edgesNr; i++) {
		if ((edges[i].u == u && edges[i].v == v)
			|| (edges[i].u == v && edges[i].v == u)) {
			return 0;
		}
	}
	return 1;
}

void updateColors(int* colors, int initialColor, int finalColor, int edgesNr) {
	for (int i = 0; i < edgesNr; i++) {
		if (colors[i] == initialColor) {
			colors[i] = finalColor;
		}
	}
}

void printMSTKruskal(Edge* minSpanTreeEdges, int mstCost, int edgesNr) {
	printf("MinSpanningTree->Edges:\n");
	for(int i = 0; i < edgesNr; i++) {
		printf("(%d) -> (%d) cost %d\n", minSpanTreeEdges[i].u, minSpanTreeEdges[i].v, minSpanTreeEdges[i].cost);
	}
	printf ("MinSpanningTree->Cost: %d\n", mstCost);
}

void Kruskal(Graph g) {
	printf("\n-------------------------------Kruskal minimum spanning tree-------------------------------\n");
	Edge* edges = (Edge *)calloc(g->E,sizeof(Edge));
	int edgeIdx = 0;

	// Add all edges by traversing each node and it's neighbours
	for (int node = 0; node < g->V; node++) {
		List neighbour = g->adjLists[node];
		while (neighbour) {
			if (validEdge(edges, node, neighbour->data.v, g->E)) {
				edges[edgeIdx].u = node;
				edges[edgeIdx].v = neighbour->data.v;
				edges[edgeIdx].cost = neighbour->data.cost;
				edgeIdx++;
			}
			neighbour = neighbour->next;
		}
	}

	// Sort edges ascending by cost
	qsort(edges, g->E, sizeof(Edge), comparatorEdges);
	int* colors = (int *)calloc(g->V, sizeof(int));
	// Assign each node a "color"
	for (int node = 0; node < g->V; node++) {
		colors[node] = node;
	}

	edgeIdx = 0;	// edges currently in the MST
	int mstCost = 0;
	Edge* minSpanTreeEdges = (Edge *)calloc(g->V - 2, sizeof(Edge));

	// Traverse sorted edges
	for (int i = 0; i < g->E; i++) {
		int clrStart = colors[edges[i].u];
		int clrEnd = colors[edges[i].v];
		
		if (clrStart != clrEnd) {
			minSpanTreeEdges[edgeIdx] = edges[i];
			mstCost += edges[i].cost;
			edgeIdx++;
			updateColors(colors, clrStart, clrEnd, g->E);
		} else if (edgeIdx == g->V - 1) {
			break;
		}
	}

	printMSTKruskal(minSpanTreeEdges, mstCost, g->V - 2);
	free(minSpanTreeEdges);
	free(edges);
}

int comparatorMinCost(const void* e1, const void* e2) {
    int p1 = (*(Pair*)e1).cost;
    int p2 = (*(Pair*)e2).cost;

	return p1 < p2;
}

void printMSTPrim(int start, int* distance, int* parent, int nodesNr) {
	printf("MinSpanningTree->Edges:\n");
	int mstCost = 0;
	for(int i = 1; i < nodesNr; i++) {
		if (i != start) {
			printf("(%d) -> (%d) cost %d\n", parent[i], i, distance[i]);
		}
		mstCost += distance[i];
	}
	printf ("MinSpanningTree->Cost: %d\n", mstCost);
}

void Prim(Graph g, int start) {
	printf("\n-------------------------------Prim minimum spanning tree-------------------------------\n");
	int* distance = (int* )calloc(g->V, sizeof(int));
	int* parent = (int* )calloc(g->V, sizeof(int));
	Heap minHeap = initHeap(comparatorMinCost);

	// Initialisation
	for (int node = 0; node < g->V; node++) {
		g->visited[node] = -1;
		parent[node] = -1;
		distance[node] = INFINITY;	
	}

	// Process starting node
	g->visited[start] = 1;
	distance[start] = 0;		
	List startNeighbours = g->adjLists[start];
	while (startNeighbours) {
		distance[startNeighbours->data.v] = startNeighbours->data.cost;
		parent[startNeighbours->data.v] = start;
		minHeap = insertHeap(minHeap, startNeighbours->data);
		startNeighbours = startNeighbours->next;
	}

	// While there is a node in heap process
	while (minHeap->size != 0) {
		// ((u, v), cost (u, v))
		Pair* node = extractMax(minHeap);
		g->visited[node->v] = 1;

		// For each neighbour corresponding to the minimum edge
		List neighbours = g->adjLists[node->v];
		while (neighbours) {
			// Add node to heap if it has not been in the heap yet
			if (g->visited[neighbours->data.v] != 1
				&& neighbours->data.cost < distance[neighbours->data.v]) {
				// Set dist[node] to edge cost
				distance[neighbours->data.v] = neighbours->data.cost;
				// Set parent of node the one extracted from heap
				parent[neighbours->data.v] = node->v;
				// Insert node in heap
				minHeap = insertHeap(minHeap, neighbours->data);
			}
			neighbours = neighbours->next;
		}
	}

	printMSTPrim(start, distance, parent, g->V);
	freeHeap(minHeap);
    free(distance);
    free(parent);
}
