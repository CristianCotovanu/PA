#include <dialog.h>
#include "graph.h"
#include "utils.h"


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

//Functie care va deseneaza graful
void drawGraph(Graph g, char *name)
{
	int i, j;
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

void rec_dfs_helper(Graph g, int node, int* visited) {
    visited[node] = 1;
    printf("%d -> ", node);

    List adj_node = g->adjLists[node];
    while (adj_node != NULL) {
        if (visited[adj_node->data] == -1) {
            rec_dfs_helper(g, adj_node->data, visited);
        }
        adj_node = adj_node->next;
    }
}

void recursiveDFS(Graph g, int start) {
    printf("------------DFS-Rec------------\n");
    printf("Starting from: %d\n", start);

    int *visited = (int *) calloc(g->V, sizeof(int));
    init_array_with(visited, -1, g->V);

    rec_dfs_helper(g, start, visited);
    printf("The End\n\n");
}

void dfs(Graph g, int start) {
    printf("------------DFS------------\n");
    printf("Starting from: %d\n", start);
    int node;
    int *visited = (int *) calloc(g->V, sizeof(int));
    int *parent = (int *) calloc(g->V, sizeof(int));
    init_array_with(visited, -1, g->V);
    init_array_with(parent, -1, g->V);

    Stack s = initStack(start);
    g->dist[start] = 0;

    while(!isEmptyStack(s)) {
        node = top(s);
        s = pop(s);

        if (visited[node] == -1) {
            visited[node] = 1;
            printf("%d -> ", node);

            List adj_node = g->adjLists[node];
            while (adj_node != NULL) {
                if (visited[adj_node->data] == -1) {
                    parent[adj_node->data] = node;
                    g->dist[adj_node->data] = 1 + g->dist[node];
                    s = push(s, adj_node->data);
                }
                adj_node = adj_node->next;
            }
        }
    }

    printf("The End\n");
    printf("Parents:");
    print_array(parent, g->V);
    printf("Distances:");
    print_array(g->dist, g->V);
    printf("\n");

    free(visited);
    free(parent);
    freeStack(s);
}

void bfs(Graph g, int start) {
    printf("------------BFS------------\n");
    printf("Starting from: %d\n", start);
    int node;
    int *visited = (int *) calloc(g->V, sizeof(int));
    int *parent = (int *) calloc(g->V, sizeof(int));
    init_array_with(parent, -1, g->V);
    init_array_with(g->dist, -1, g->V);

    visited[start] = 1;
    parent[start] = -1;
    g->dist[start] = 0;

    Queue q = initQueue(start);

    while (!isEmptyQueue(q)) {
        node = first(q);
        q = dequeue(q);

        List adj_node = g->adjLists[node];
        while (adj_node != NULL) {
            if (!visited[adj_node->data]) {
                parent[adj_node->data] = node;
                g->dist[adj_node->data] = 1 + g->dist[parent[adj_node->data]];
                q = enqueue(q, adj_node->data);
                visited[adj_node->data] = 1;
            }
            adj_node = adj_node->next;
        }
    }

    printf("Parents:");
    print_array(parent, g->V);
    printf("Distances:");
    print_array(g->dist, g->V);
    printf("\n");

    free(visited);
    free(parent);
    freeQueue(q);
}

void topoSortKhanAlgorithm(Graph g) {
    printf("------------Topological Sort Khan Algorithm------------\n");
    int* indegree = g->indegree;
    List S = NULL;

    for (int i = 0; i < g->V; i++) {
        if (!indegree[i]) {
            S = addFirst(S, i);
        }
    }

    int nodeCnt = 0;
    List top_order = NULL;

    while (S != NULL) {
        int node = S->data;
        S = deleteItem(S, S->data);

        top_order = addLast(top_order, node);


        List adjNode = g->adjLists[node];

        while (adjNode != NULL) {
            indegree[adjNode->data]--;
            if (indegree[adjNode->data] == 0) {
                S = addFirst(S, adjNode->data);
            }
            adjNode = adjNode->next;
        }
        nodeCnt++;
    }

    if (nodeCnt != g->V) {
        printf("There is a cycle\n");
        return;
    }

    printf("Topological order: ");
    while (top_order != NULL) {
        printf(" %d -> ", top_order->data);
        top_order = top_order->next;
    }
    freeList(top_order);
    freeList(S);
    printf("The End\n");
}

// void print_topo_sort(int* v, int len) {
//     int originalIdx[len];
//     for (int i = 0; i < len; i++) {
//         originalIdx[i] = i;
//     }
//
//     for (int i = 0; i < len; i++) {
//         for (int j = i; j < len; j++) {
//             if (v[i] > v[j]) {
//                 swap(&v[i], &v[j]);
//                 swap(&originalIdx[i], &originalIdx[j]);
//             }
//         }
//     }
//
//     printf("Topological Order: \n");
//     print_array(originalIdx, len);
// }
//
// int isGraphVisited(int* visited, int len) {
//     for (int i = 0; i < len; i++) {
//         if (visited[i] != 1) {
//             return 0;
//         }
//     }
//     return 1;
// }
//
// int getUnvisitedNode(int* visited, int len) {
//     for (int i = 0; i < len; i++) {
//         if (visited[i] != 1) {
//             return i;
//         }
//     }
//
//     printf("[Err]All nodes were visited\n");
//     return -7;
// }
//
// int allChildrenVisited(Graph g, int node, int* visited) {
//     List adj_node = g->adjLists[node];
//     while (adj_node != NULL) {
//         if (visited[adj_node->data] != 1) {
//             return 0;
//         }
//         adj_node = adj_node->next;
//     }
//     return 1;
// }
//
// void topologicalSortDfs(Graph g) {
//     printf("------------Topological Sort DFS------------\n");
//     int node;
//     int *visited = (int *) calloc(g->V, sizeof(int));
//     int *end_time = (int *) calloc(g->V, sizeof(int));
//     int *discovery_time = (int *) calloc(g->V, sizeof(int));
//     init_array_with(visited, -1, g->V);
//     init_array_with(end_time, -7, g->V);
//     init_array_with(discovery_time, -7, g->V);
//
//     int flag_cycle = 0;
//     int time = 1;
// //    int start_node = rand() % g->V;
// //    int start_node = 0;
//
//     Stack s = NULL;
// //    discovery_time[start_node] = time++;
//
//     while (!isGraphVisited(visited, g->V)) {
//         node = getUnvisitedNode(visited, g->V);
//         s = push(s, node);
//         discovery_time[node] = time++;
//         printf("%d -> ", node);
//
//         while(!isEmptyStack(s)) {
//             node = top(s);
//             s = pop(s);
//
//             if (visited[node] == -1) {
//                 visited[node] = 1;
//
//                 List adj_node = g->adjLists[node];
//                 while (adj_node != NULL) {
//                     if (visited[adj_node->data] == -1) {
//                         printf("%d -> ", adj_node->data);
//
//                         discovery_time[adj_node->data] = time++;
//                         s = push(s, adj_node->data);
//                     }
//                     adj_node = adj_node->next;
//                 }
//             } else {
//                 flag_cycle = 1;
//             }
////             if (allChildrenVisited(g, node, visited) == 1) {
////                 end_time[node] = time++;
////             }
//             printf("\n");
//         }
//     }
//     printf("Discovery: ");
//     print_array(discovery_time, g->V);
//     printf("Ends: ");
//     print_array(end_time, g->V);
//
//     flag_cycle == 1 ? printf("Cyclic graph, topological sort not possible\n") : print_topo_sort(end_time, g->V);
//
//     free(visited);
//     free(discovery_time);
//     free(end_time);
//     freeStack(s);
// }