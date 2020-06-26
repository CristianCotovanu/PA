#include "graph.h"
#include "graph_utils.h"

Graph initGraph(int V, int type) {
	Graph graph;
	graph = malloc(sizeof(struct graph));
	graph->V = V;
	graph->type = type;
	graph->dist = calloc(V, sizeof(int));
	graph->indegree = calloc(V, sizeof(int));
	graph->adjLists = calloc(V, sizeof(List));
	return graph;
}

Graph insertEdge(Graph g, int u, int v) {
	g->adjLists[u] = addLast(g->adjLists[u], v);
	g->indegree[v]++;
	if (g->type == 0)
		g->adjLists[v] = addLast(g->adjLists[v], u);
	return g;
}

void drawGraph(Graph g, char *name)
{
	int i;
	FILE *stream;
	char *buffer;
	List tmp;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	fprintf(stream, "graph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->V; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			if (tmp->data > i)
				fprintf(stream, "    %d -- %d;\n", i, tmp->data);
			tmp = tmp->next;
		}
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot %s | neato -n -Tpng -o graph.png", name);
	system(buffer);
	free(buffer);
}

// O(V+E)
void dfs_art_points(Graph g, int vertex, int* visited, int *discover, int *low, int *parent, int *time, int *result, int *children) {
    visited[vertex] = 1;
    discover[vertex] = low[vertex] = ++(*time);

    List adj_nodes = g->adjLists[vertex];
    while (adj_nodes != NULL) {
        if (visited[adj_nodes->data] == 0) {
            (*children)++;
            parent[adj_nodes->data] = vertex;
            dfs_art_points(g, adj_nodes->data, visited, discover, low, parent, time, result, children);

            low[vertex]  = min(low[vertex], low[adj_nodes->data]);

            // articulation points condition
            if (parent[vertex] == -1 && *children > 1) {
                result[vertex] = 1;
            } else if (parent[vertex] != -1 && discover[vertex] <= low[adj_nodes->data]) {
                result[vertex] = 1;
            }
        } else if (adj_nodes->data != parent[vertex]) {
            low[vertex] = min(low[vertex], discover[adj_nodes->data]);
        }
        adj_nodes = adj_nodes->next;
    }
}

// O(V * (V + E))
void articulationPointsTarjan(Graph g) {
    printf("-------------------------------Tarjan Articulation Points-------------------------------\n");
    int *visited = (int *)calloc(g->V, sizeof(int));
    int *discover = (int *)calloc(g->V, sizeof(int));
    int *low = (int *)calloc(g->V, sizeof(int));
    int *parent = (int *)calloc(g->V, sizeof(int));
    int *result = (int *)calloc(g->V, sizeof(int));
    int time = 0;
    int children = 0;

    for (int i = 0; i < g->V; i++) {
        parent[i] = -1;
    }

    for (int i = 0; i < g->V; i++) {
        if (visited[i] == 0) {
            dfs_art_points(g, i, visited, discover, low, parent, &time, result, &children);
        }
    }

    printf("Articulation points: ");
    for (int i = 0; i < g->V; i++) {
        if (result[i] == 1) {
            printf("%d ", i + 1);
        }
    }

    free(visited);
    free(discover);
    free(low);
    free(result);
    free(parent);
    printf("\n\n");
}


// O(V+E)
void dfs_bridges(Graph g, int vertex, int *visited, int *discover, int *low, int *parent, int *time, int *children) {
    visited[vertex] = 1;
    discover[vertex] = low[vertex] = ++(*time);

    List adj_nodes = g->adjLists[vertex];
    while (adj_nodes != NULL) {
        if (visited[adj_nodes->data] == 0) {
            (*children)++;
            parent[adj_nodes->data] = vertex;

            dfs_bridges(g, adj_nodes->data, visited, discover, low, parent, time, children);
            low[vertex]  = min(low[vertex], low[adj_nodes->data]);

            // bridge condition
            if (low[adj_nodes->data] > discover[vertex]) {
                printf("(%d, %d) ", vertex + 1, adj_nodes->data + 1);
            }
        } else if (adj_nodes->data != parent[vertex]) {
            //  if visited -> update low time
            low[vertex] = min(low[vertex], discover[adj_nodes->data]);
        }

        adj_nodes = adj_nodes->next;
    }
}

// O(V * (V + E))
void bridgesTarjan(Graph g) {
    printf("-------------------------------Tarjan Bridges-------------------------------\n");
    int *visited = (int *)calloc(g->V, sizeof(int));
    int *discover = (int *)calloc(g->V, sizeof(int));
    int *low = (int *)calloc(g->V, sizeof(int));
    int *parent = (int *)calloc(g->V, sizeof(int));
    int time = 0;
    int children = 0;

    for (int i = 0; i < g->V; i++) {
        parent[i] = -1;
    }

    printf("Bridges:\n");
    for (int i = 0; i < g->V; i++) {
        if (visited[i] == 0) {
            dfs_bridges(g, i, visited, discover, low, parent, &time, &children);
        }
    }
    printf("\n\n");
}