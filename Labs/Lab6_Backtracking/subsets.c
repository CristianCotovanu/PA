#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_array(int len, int* v) {
    for (int i = 0; i < len; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void print_subset(int* S, int* sequence, int size) {
    printf("{");
//    Daca unui element ii este asociat 1 in sequence, acesta face parte din submultimea curenta
    for (int i = 0; i < size; i++) {
        if (sequence[i] == 1) {
            printf("%d ", S[i]);
        }
    }
    printf("}\n");
}

//  S = multimea totala
//  idx = indexul pentru parcurgerea lui sequence
//  sequence = vector pentru a retine daca elem crt face parte din submultime crt
//  size = marimea multimii

//  D.p.d.v spatial algoritmul poate fi optimizat si anume, sequence poate fi un int in care vom seta bitii corespunzatori
//  comparativ cu vectorul alocat

//  Complexitate: 2*T(n - 1) + O(1)
void subset(int* S, int idx, int* sequence, int size) {
    if (idx >= size) {
        print_subset(S, sequence, size);
        return;
    } else {
        sequence[idx] = 0;
        subset(S, idx + 1, sequence, size);
        sequence[idx] = 1;
        subset(S, idx + 1, sequence, size);
    }
}


void test1() {
    int S[] = {1, 2, 3};
    int size = 3;
    int* sequence = calloc(size, sizeof(int));
    int idx = 0;
    printf("=========test1=========\n");
    printf("Initial array: ");
    print_array(size, S);
    subset(S, idx, sequence, size);
    printf("\n");
}

void test2() {
    int S[] = {11, 22, 33, 44, 55};
    int size = 5;
    int* sequence = calloc(size, sizeof(int));
    int idx = 0;
    printf("=========test2=========\n");
    printf("Initial array: ");
    print_array(size, S);
    subset(S, idx, sequence, size);
    printf("\n");
}

void test3() {
    int S[] = {};
    int size = 0;
    int* sequence = calloc(size, sizeof(int));
    int idx = 0;
    printf("=========test3=========\n");
    printf("Initial array: ");
    print_array(size, S);
    subset(S, idx, sequence, size);
    printf("\n");
}

int main() {
    printf("---------------------------------Subsets---------------------------------\n\n");

    test1();
    test2();
    test3();

    return 0;
}
