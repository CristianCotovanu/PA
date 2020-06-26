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

void StronglyConnectedComponentsKosaraju(Graph g);
int ChooseUnvisitedNode(int* visited, int len);
void DfsTopoSortBuildStack(Graph g, int node, int* state, int* visited, Stack* stack);
void DfsReverseGraph(List* transposedAdj, int node, List* components, int* state);
int ContainsAllVertices(int* visited, int len);


#endif

