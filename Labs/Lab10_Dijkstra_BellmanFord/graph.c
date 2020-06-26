#include <string.h>
#include "graph.h"
#include "stack.h"
#include "heap.h"

Graph initGraph(int V, int type)
{
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

Graph insertEdge(Graph g, int u, int v, int cost)
{
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

int isArc(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return INFINITY;
}

void drawGraph(Graph g, char *name)
{
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

void printGraph(Graph g)
{
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

Graph freeGraph(Graph graph)
{
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

int compareMin(const void* e1, const void* e2) {
    Pair p1 = *(Pair*) e1;
    Pair p2 = *(Pair*) e2;

    if (p1.cost < p2.cost) {
        return -1;
    } else if (p1.cost == p2.cost) {
        return 0;
    } else {
        return 1;
    }
}

void printCost(int verticesNr, int startNode, int* parent, int* distance) {
    for (int node = 0; node < verticesNr; node++) {
        if (node != startNode) {
            printf("\nMinDist from (%d) to (%d) with cost %d.\n", startNode, node, distance[node]);

            int tmp = node;
            Stack printStack = initStack(tmp);
            while (parent[tmp] != -1) {
                tmp = parent[tmp];
                printStack = push(printStack, tmp);
            }

            while (!isEmptyStack(printStack)) {
                printf("%d -> ", top(printStack));
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

void Dijkstra(Graph g, int start) {
    printf("\n-------------------------------Dijkstra finding minimum distance-------------------------------");
    int* distance = (int* )calloc(g->V, sizeof(int));
    int* parent = (int* )calloc(g->V, sizeof(int));
    Heap minHeap = initHeap(compareMin);

    g->visited[start] = 1;

    for (int node = 0; node < g->V; node++) {
        if (start != node && isArc(g, start, node)) {
            distance[node] = getCost(g, start, node);
            parent[node] = start;

            Type t;
            t.v = node;
            t.cost = distance[node];
            minHeap = insertHeap(minHeap, t);
        } else {
            distance[node] = INFINITY;
            parent[node] = -1;
        }
    }

    while (minHeap->size != 0) {
        Type node = extractMax(minHeap);
//        printf("Nod extras:%d cost:%d dist:%d\n", node.v, node.cost, distance[node.v]);
        g->visited[node.v] = 1;
        for (List neighbours = g->adjLists[node.v]; neighbours != NULL; neighbours = neighbours->next) {
            if (distance[neighbours->data.v]
                    > distance[node.v] + getCost(g, node.v, neighbours->data.v)) {

                distance[neighbours->data.v] = distance[node.v] + getCost(g, node.v, neighbours->data.v);
                parent[neighbours->data.v] = node.v;
                minHeap = insertHeap(minHeap, neighbours->data);
            }
        }
    }


    printCost(g->V, start, parent, distance);
    freeHeap(minHeap);
    free(distance);
    free(parent);
}

void BellmanFord(Graph g, int start) {
    printf("\n-------------------------------Bellman-Ford finding minimum distance-------------------------------");
    int* distance = (int* )calloc(g->V, sizeof(int));
    int* parent = (int* )calloc(g->V, sizeof(int));

    for (int node = 0; node < g->V; node++) {
        if (start != node && isArc(g, start, node)) {
            distance[node] = getCost(g, start, node);
            parent[node] = start;
        } else {
            distance[node] = INFINITY;
            parent[node] = -1;
        }
    }
    distance[start] = 0;
    parent[start] = -1;

    for (int i = 0; i < g->V - 1; i++) {
        for (int node = 0; node < g->V; node++) {
            for (List neighbours = g->adjLists[node]; neighbours != NULL; neighbours = neighbours->next) {
                if (distance[neighbours->data.v] > distance[node] + getCost(g, node, neighbours->data.v)) {
                    distance[neighbours->data.v] = distance[node] + getCost(g, node, neighbours->data.v);
                    parent[neighbours->data.v] = node;
                }
            }
        }
    }

    int negativeCycle = 0;
    for (int node = 0; node < g->V; node++) {
        for (List neighbours = g->adjLists[node];neighbours != NULL; neighbours = neighbours->next) {
            if (distance[neighbours->data.v] > distance[node] + getCost(g, node, neighbours->data.v)) {
                printf("Failure graph contains a negative cycle.\n");
                negativeCycle = 1;
                break;
            }
        }
    }

    if (!negativeCycle) {
        printCost(g->V, start, parent, distance);
    }

    free(distance);
    free(parent);
}
