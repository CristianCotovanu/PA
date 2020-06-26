#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"
#include "stack.h"

#define SIZE 200

typedef struct graph {
	int V, *dist, *indegree;
	List *adjLists;
	int type; // 0 - neorientat | 1 - orientat
}*Graph;

Graph initGraph(int V, int type);
Graph insertEdge(Graph g, int u, int v);
void drawGraph(Graph g, char *name);

void articulationPointsTarjan(Graph g);
void bridgesTarjan(Graph g);

#endif

