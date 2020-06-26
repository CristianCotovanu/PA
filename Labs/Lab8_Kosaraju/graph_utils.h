#include <stdlib.h>

void swap(int* x, int* y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void init_array_with(int* array, int value, int len) {
    for (int i = 0; i < len; ++i){
        array[i] = value;
    }
}

void print_array(int* v, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void printEdges(List *adjLists) {
    for (int i = 0; i < 9; i++) {
        List adjNode = adjLists[i];
        printf("%d has: ", i);
        while (adjNode != NULL) {
            printf(" %d ->", adjNode->data);
            adjNode = adjNode->next;
        }
        printf("\n");
    }
}
