#include <stdio.h>
#include "utils.h"

//    complexity: O(items_nr * weight_cap)
int knapsack(int items_nr, int weight_cap, int* price, int* weight) {
//    dp[i][j] - stores
    int** dp = matrix_alloc(items_nr + 1, weight_cap + 1);
//    base case: weight-cap = 0 => no objets in the bag => dp[0][i] = 0;
//    general case: build dp[i][w] with objects up to "i"th and weight-cap up to "w"
    for (int i = 1; i < items_nr + 1; i++) {
        for (int w = 1; w < weight_cap + 1; w++) {
//            check for valid idx
//            if current obj would increase the value add it else keep the last value
            if (w - weight[i - 1] >= 0) {
                dp[i][w] = max_of_two(dp[i - 1][w - weight[i - 1]] + price[i - 1], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

//    max profit consists of using all objects and the maximum weight_cap
    int max_profit = dp[items_nr][weight_cap];
    free_matrix(items_nr + 1, dp);

    return max_profit;
}

void test1() {
    int price[] = {1, 2, 5, 6};
    int weight[] = {2, 3, 4, 5};
    printf("test1-knapsacked_money: %d\n", knapsack(4, 8, price, weight));
    printf("prices: ");
    print_array(4, price);
    printf("weights: ");
    print_array(4, weight);
    printf("\n");
}

void test2() {
    int price[] = {7, 4, 2, 9, 4, 5};
    int weight[] = {3, 3, 1, 1, 2, 1};
    printf("test2-knapsacked_money: %d\n", knapsack(6, 10, price, weight));
    printf("prices: ");
    print_array(6, price);
    printf("weights: ");
    print_array(6, weight);
    printf("\n");
}

void test3() {
    int price[] = {60, 100, 120};
    int weight[] = {10, 20, 25};
    printf("test3-knapsacked_money: %d\n", knapsack(3, 50, price, weight));
    printf("prices: ");
    print_array(3, price);
    printf("weights: ");
    print_array(3, weight);
    printf("\n");
}

int main() {
    printf("----------------------------------0/1 Knapsack----------------------------------\n");
    test1();
    test2();
    test3();

    return 0;
}
