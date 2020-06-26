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

void drawGraph(Graph g, char *name) {
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
    buffer = (char *) malloc(SIZE * sizeof(char));
    sprintf(buffer, "dot %s | neato -n -Tpng -o graph.png", name);
    system(buffer);
    free(buffer);
}

int ChooseUnvisitedNode(int *visited, int len) {
    for (int i = 0; i < len; i++) {
        if (visited[i] != 1) {
            return i;
        }
    }
    printf("[ERROR] All nodes are visited\n");
    return -1;
}

void PrintStConnectedComponents(List list) {
    // indexarea a fost facuta de la 0 pentru noduri
    // asa ca am adaugat la final un 1
    if (list != NULL) {
        printf("Component {");
        while (list != NULL) {
            if (list->next == NULL) {
                printf("%d", list->data + 1);
                break;
            }
            printf("%d, ", list->data + 1);
            list = list->next;
        }
        printf("}\n");
    }
}

void DfsTopoSortBuildStack(Graph g, int node, int *state, int *visited, Stack *stack) {
    state[node] = 1;
    List adj_nodes = g->adjLists[node];

    while (adj_nodes != NULL) {
        if (state[adj_nodes->data] == 0) {
            DfsTopoSortBuildStack(g, adj_nodes->data, state, visited, stack);
        }
        adj_nodes = adj_nodes->next;
    }
    state[node] = -1;
    *stack = push(*stack, node);
    visited[node] = 1;
}

void DfsReverseGraph(List *transposedAdj, int node, List *components, int *state) {
    state[node] = 1;
    List adj_nodes = transposedAdj[node];

    while (adj_nodes != NULL) {
        if (state[adj_nodes->data] == 0) {
            DfsReverseGraph(transposedAdj, adj_nodes->data, components, state);
        }
        adj_nodes = adj_nodes->next;
    }
    *components = addLast(*components, node);
    state[node] = -1;
}

// functie auxiliara pentru a verifica daca toate nodurile sunt puse in stack pe baza unui vector de vizitare
int ContainsAllVertices(int *visited, int len) {
    for (int i = 0; i < len; i++) {
        if (visited[i] != 1) {
            return 0;
        }
    }
    return 1;
}

void StronglyConnectedComponentsKosaraju(Graph g) {
    printf("-------------------------------Kosaraju Strongly Connected Components-------------------------------\n");
    int *visited = (int *) calloc(g->V, sizeof(int));
    int *state = (int *) calloc(g->V, sizeof(int));
    Stack stack = NULL;
    int node;
    int sccCount = 0;

    while (!ContainsAllVertices(visited, g->V)) {
        node = ChooseUnvisitedNode(visited, g->V);
        DfsTopoSortBuildStack(g, node, state, visited, &stack);
    }

    // transpunerea grafului prin crearea unei noi liste de adiacenta cu muchiile initiale inversate
    List *transposedAdjList = (List *) calloc(g->V, sizeof(List));

    for (int i = 0; i < g->V; i++) {
        List adj_nodes = g->adjLists[i];
        while (adj_nodes != NULL) {
            transposedAdjList[adj_nodes->data] = addLast(transposedAdjList[adj_nodes->data], i);
            adj_nodes = adj_nodes->next;
        }
    }

    if (stack == NULL) {
        printf("[ERROR] First step, failed, invalid graph\n");
    }

    init_array_with(state, 0, g->V);

    while (!isEmptyStack(stack)) {
        List crtComponent = NULL;

        if (state[top(stack)] == -1) {
            stack = pop(stack);
        } else {
            DfsReverseGraph(transposedAdjList, top(stack), &crtComponent, state);
            stack = pop(stack);
        }

        if (crtComponent != NULL) {
            PrintStConnectedComponents(crtComponent);
            sccCount++;
        }
    }

    printf("We have %d strongly connected components.\n", sccCount);
}