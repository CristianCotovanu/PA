#include <stdio.h>
#include "utils.h"

//    return maximum number of pieces (of length a || b || c) in which a ribbon can be cut
//    complexity: O(n)
int cut_ribbon(int n, int a, int b, int c) {
//    store max number of piece if using only "i" length of ribbon
    int dp[n + 1];
//    base case: dp[i] = 0 with i < smallest(a, b, c), can't make any cut
    zero_array(n + 1, dp);

    for(int i = 1; i < n + 1; i++) {
//        check for invalid indices in dp
        int using_cut_a = i - a >= 0 ? dp[i - a] : -1;
        int using_cut_b = i - b >= 0 ? dp[i - b] : -1;
        int using_cut_c = i - c >= 0 ? dp[i - c] : -1;

//        if cut is valid get current piece (+ 1) + maximum of remaining ribbon length
        if (using_cut_a == -1 && using_cut_b == -1 && using_cut_c == -1) {
            dp[i] = -1;
        } else {
            dp[i] = 1 + max_of_three(using_cut_a, using_cut_b, using_cut_c);
        }
    }
//    return max cuts when the whole ribbon is used
    return dp[n];
}

int test1() {
    return cut_ribbon(5, 5, 3, 2);
}

int test2() {
    return cut_ribbon(27, 2, 9, 7);
}

int test3() {
    return cut_ribbon(16, 7, 5, 3);
}


int main() {
    printf("----------------------------------CUT RIBBON----------------------------------\n");
    printf("test1: %d\n", test1());
    printf("test2: %d\n", test2());
    printf("test3: %d\n", test3());

    return 0;
}
