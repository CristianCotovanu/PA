#include <stdlib.h>

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

void zero_array(int len, int* v) {
    for (int i = 0; i < len; i++) {
        v[i] = 0;
    }
}

void free_matrix(int rows, int** matrix) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
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

void print_array(int len, int* v) {
    for (int i = 0; i < len; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int** matrix_alloc(int rows, int cols) {
    int** dp = (int **) calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        dp[i] = (int *) calloc(cols, sizeof(int));
    }

    return dp;
}
