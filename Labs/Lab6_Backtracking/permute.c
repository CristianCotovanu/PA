#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  S = initial group
//  size = size of S
//  solution = current permutation
//  idx = nr. of elems in current permutation

//  Complexitate: O(n^2 * n!)
void permute(char* S, char* solution, int size, int idx) {
//  crt permutation is a valid permutation
    if (size == idx) {
        printf("%s\n", solution);
        return;
    }

    for (int i = 0; i < size; i++) {
        if (strchr(solution, S[i])) {
            continue;
        }

        solution[idx] = S[i];
        permute(S, solution, size, idx + 1);
        solution[idx] = '\0';
    }
}

void test1() {
    char* S = "0\0";
    char* sol = calloc(1 + strlen(S), sizeof(char));
    int len = strlen(S);
    int idx = 0;
    printf("=========test1=========\n");
    permute(S, sol, len, idx);
    printf("\n");
}

void test2() {
    char* S = "123\0";
    char* sol = calloc(1 + strlen(S), sizeof(char));
    int len = strlen(S);
    int idx = 0;
    printf("=========test2=========\n");
    permute(S, sol, len, idx);
    printf("\n");
}

void test3() {
    char* S = "abcd\0";
    char* sol = calloc(1 + strlen(S), sizeof(char));
    int len = strlen(S);
    int idx = 0;
    printf("=========test3=========\n");
    permute(S, sol, len, idx);
    printf("\n");
}

int main() {
    printf("---------------------------------Permutations---------------------------------\n\n");

    test1();
    test2();
    test3();

    return 0;
}