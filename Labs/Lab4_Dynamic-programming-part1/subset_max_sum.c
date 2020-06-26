#include <stdio.h>
#include "utils.h"

//    complexity: O(n)
void subset_max_sum(int n, int* array) {
//    stores max sum of elements up to "i"
    int dp[n];
//    stores starting indices for max sum of elems 0:i
    int start[n];
    zero_array(n, dp);
    zero_array(n, start);

//  base case: first element
    dp[0] = array[0];

//  general case: build max_sum using only elements up to "i"th
    for (int i = 1; i < n; i++) {
        if (dp[i - 1] >= 0) {
            dp[i] = dp[i - 1] + array[i];
            start[i] = start[i - 1];
        } else {
            dp[i] = array[i];
            start[i] = i;
        }
    }

// solution: max sum from dp
    int max_sum = dp[0];
    int m_s_idx = 0;

    for (int i = 1; i < n; ++i) {
        if (dp[i] > max_sum) {
            max_sum = dp[i];
            m_s_idx = i;
        }
    }

    printf("maximum sum is: %d from v[%d] to v[%d]\n", max_sum, start[m_s_idx], m_s_idx);
    printf("subset max sum: ");
    for (int j = start[m_s_idx]; j <= m_s_idx; j++) {
        printf("%d ", array[j]);
    }
}

int test1() {
    int array[] = {1, -7, 8, 8, 8, -200};
    printf("input array: ");
    print_array(6, array);
    subset_max_sum(6, array);
    printf("\n\n");
}

int test2() {
    int array[] = {5, -6, 3, 4, -2, 3, -3};
    printf("input array: ");
    print_array(7, array);
    subset_max_sum(7, array);
    printf("\n\n");
}

int test3() {
    int array[] = {-7, -8, -9, -100, -6, -1, -93};
    printf("input array: ");
    print_array(7, array);
    subset_max_sum(7, array);
    printf("\n");
}

int main() {
    printf("----------------------------------Subset Max Sum----------------------------------\n");
    printf("test1: ");
    test1();
    printf("test2: ");
    test2();
    printf("test3: ");
    test3();

    return 0;
}
