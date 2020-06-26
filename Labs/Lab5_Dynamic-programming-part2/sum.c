#include <stdio.h>
#include "utils.h"

int sum(int array[], int n) {
//    each row stands for how many sums would be if we were using numbers up to the "i"th element
//    each column stores number of sums that have a remainder from {0, 1, 2}
    int** dp = matrix_alloc(n, 3);

//    base case: 0/1 if the number has or does not have 0,1,2 remainder to div by 3
    dp[0][0] = array[0] % 3 == 0 ? 1 : 0;
    dp[0][1] = array[0] % 3 == 1 ? 1 : 0;
    dp[0][2] = array[0] % 3 == 2 ? 1 : 0;

//    general case: add it to specific column based on remainder
    for (int i = 1; i < n; i++) {
        if (array[i] % 3 == 0) {
            dp[i][0] = 1 + 2 * dp[i - 1][0];
            dp[i][1] = 2 * dp[i - 1][1];
            dp[i][2] = 2 * dp[i - 1][2];
        } else if (array[i] % 3 == 1) {
            dp[i][0] = dp[i - 1][0] + dp[i - 1][2];
            dp[i][1] = 1 + dp[i - 1][0] + dp[i - 1][1];
            dp[i][2] = dp[i - 1][2] + dp[i - 1][1];
        } else if (array[i] % 3 == 2) {
            dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
            dp[i][1] = dp[i - 1][2] + dp[i - 1][1];
            dp[i][2] = 1 + dp[i - 1][2] + dp[i - 1][0];
        }
    }

//    return n-1 th element with remainder 0 to division by 3
    return dp[n - 1][0];
}

void test0() {
    printf("=========test0=========\n");
    int array[] = {4, 4};
    printf("Input array: ");
    print_array(2, array);
    printf("Nr. of sums: %d\n\n", sum(array, 2));
}

void test1() {
    printf("=========test1=========\n");
    int array[] = {1, 2, 3};
    printf("Input array: ");
    print_array(3, array);
    printf("Nr. of sums: %d\n\n", sum(array, 3));
}

void test2() {
    printf("=========test2=========\n");
    int array[] = {7, 7, 7, 7, 7, 7};
    printf("Input array: ");
    print_array(6, array);
    printf("Nr. of sums: %d\n\n", sum(array, 6));
}

void test3() {
    printf("=========test3=========\n");
    int array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    printf("Input array: ");
    print_array(10, array);
    printf("Nr. of sums: %d\n\n", sum(array, 10));
}

int main() {
    printf("---------------------------------Sum---------------------------------\n\n");

    test0();
    test1();
    test2();
    test3();

    return 0;
}
