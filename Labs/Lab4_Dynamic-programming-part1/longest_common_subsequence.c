#include <stdio.h>
#include "utils.h"

//    complexity for computing length: O(len_A * len_B)
//    complexity for finding LCS: O(max(len_A, len_B))
//    total complexity: O(len_A * len_B * max(len_A, len_B)
void longest_commmon_subsequence(int len_A, int* A, int len_B, int* B) {
//    store length of LCS for each array using elements up to an idx
    int** dp = matrix_alloc(len_A + 1, len_B + 1);

    for (int i = 1; i < len_A + 1; i++) {
        for (int j = 1; j < len_B + 1; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max_of_two(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    printf("Length of LCS is: %d\n", dp[len_A][len_B]);

    int i = len_A;
    int j = len_B;
    int lcs_len = dp[len_A][len_B];
    int* lcs = (int *)calloc(lcs_len, sizeof(int));

//    traverse A and B backwards to find common elements
    while (i > 0 && j > 0) {
//        if curr element is common, add it to lcs
        if (A[i - 1] == B[j - 1]) {
            lcs[lcs_len - 1] = A[i - 1];
            i--;
            j--;
            lcs_len--;
//        else advance in longer arr
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS is: ");
    print_array(dp[len_A][len_B], lcs);
    free_matrix(len_A, dp);
    free(lcs);
}

int test0() {
    int A[] = {5, 4, 4, 3, 2, 1};
    int B[] = {1, 2, 2, 3, 3, 3};
    printf("A: ");
    print_array(6, A);
    printf("B: ");
    print_array(6, B);

    longest_commmon_subsequence(6, A, 6, B);
    printf("\n");
}

int test1() {
    int A[] = {1, 2, 2, 3, 3, 3};
    int B[] = {1, 2, 2, 3, 3, 3};
    printf("A: ");
    print_array(6, A);
    printf("B: ");
    print_array(6, B);

    longest_commmon_subsequence(6, A, 6, B);
    printf("\n");
}

int test2() {
    int A[] = {'M', 'B', 'N', 'D', 'L', 'F', 'T', 'G'};
    int B[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    printf("A: ");
    print_array(8, A);
    printf("B: ");
    print_array(7, B);

    longest_commmon_subsequence(8, A, 7, B);
    printf("\n");
}

int test3() {
    int A[] = {7, 10, 5, 3, 2, 8, 11, 15, 54};
    int B[] = {1, 1, 10, 2, 88, 6, 7, 11, 99, 54};
    printf("A: ");
    print_array(9, A);
    printf("B: ");
    print_array(10, B);

    longest_commmon_subsequence(9, A, 10, B);
    printf("\n");
}

int main() {
    printf("----------------------------------Max Length Subarray in two vectors----------------------------------\n");
    printf("====test0====\n");
    test0();
    printf("====test1====\n");
    test1();
    printf("====test2====\n");
    test2();
    printf("====test3====\n");
    test3();

    return 0;
}
