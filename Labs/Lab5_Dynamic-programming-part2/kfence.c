#include <stdlib.h>
#include <stdio.h>

int kfence(int n, int k) {
//    stores ways of putting the wood piece to make a fence of length up to the current idx
    int dp[n];

//    base case: only vertical way to put wood pieces to build a fence of len < k
    dp[k - 1] = 2;
    for (int i = 0; i < k - 1; i++) {
        dp[i] = 1;
    }

//    general case: add way of building the fence
    for (int i = k; i < n; ++i) {
        dp[i] = dp[i - 1] + dp[i - k];
    }

    return dp[n - 1];
}

void test1() {
    int n = 9;
    int k = 4;
    printf("=========test1=========\n");
    printf("Length: %d height: %d\n", n, k);
    printf("Ways of building the fence: %d\n\n", kfence(n, k));
}

void test2() {
    int n = 1;
    int k = 4;
    printf("=========test2=========\n");
    printf("length: %d, height: %d\n", n, k);
    printf("Ways of building the fence: %d\n\n", kfence(n, k));
}

void test3() {
    int n = 16;
    int k = 15;
    printf("=========test3=========\n");
    printf("length: %d, height: %d\n", n, k);
    printf("Ways of building the fence: %d\n\n", kfence(n, k));
}

int main() {
    printf("---------------------------------K-Fence---------------------------------\n\n");

    test1();
    test2();
    test3();

    return 0;
}
