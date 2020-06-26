#include <stdlib.h>

void swap(int* x, int* y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

int max_of_two(int a, int b) {
    return a > b ? a : b;
}

int max_of_three(int a, int b, int c) {
    if (a > b) {
        if (a > c) {
            return a;
        } else {
            return c;
        }
    } else if (b > c) {
        return b;
    } else {
        return c;
    }
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


void print_matrix(int rows, int cols, int** matrix) {
    for (int i = 0; i < rows; i++) {
        printf("[");
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("]\n");
    }
}

void free_matrix(int rows, int** matrix) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** matrix_alloc(int rows, int cols) {
    int** dp = (int **) calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        dp[i] = (int *) calloc(cols, sizeof(int));
    }

    return dp;
}
